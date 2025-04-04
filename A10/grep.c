/**
 * Name: Reagan Buvens
 * Date: 04/04/2025
 * Description: Given a list of files and a target keyword or expression, uses
 * multiple threads to efficiently search for the target in the files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *search(void *arg) {
  void **args = (void **) arg;
  int id = *(int*) args[0];
  int numFiles = *(int*) args[1];
  char **files = (char**) args[2];
  char *target = (char*) args[3]; 

  int hits = 0;

  for (int i = 0; i < numFiles; i++) {
    FILE *fp = fopen(files[i], "r");
    if (!fp) {
      printf("Error opening file %d in thread %d\n", i, id);
      continue;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
      if (strstr(line, target)) {
        hits++;
      }
    }
    fclose(fp);
  }

  printf("Thread %d found %d lines containing target: %s\n", id, hits, target);
  free(args[0]);
  free(args[1]);
  free(args);
  return NULL;
}

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("usage: ./grep <Num_Threads> <Keyword> <Files>\n");
    return 1;
  }

  int numT = atoi(argv[1]);
  char *target = argv[2];
  int numFiles = argc - 3;
  char **files = &argv[3];

  pthread_t *threads = malloc(sizeof(pthread_t) * numT);
  int fPerT = numFiles / numT;
  int leftover = numFiles % numT;

  int idx = 0;
  for (int i = 0; i < numT; i++) {
    int num = fPerT;
    if (i < leftover) { num++; }

    void **args = malloc(sizeof(void*) * 4);
    args[0] = malloc(sizeof(int));
    *(int*)args[0] = i;
    args[1] = malloc(sizeof(int));
    *(int*)args[1] = num;
    args[2] = &files[idx];
    args[3] = target;

    pthread_create(&threads[i], NULL, search, args);

    printf("Thread %d searching %d files (%d to %d)\n", i, num, idx, idx + num);

    idx += num;
  }

  for (int i = 0; i < numT; i++) {
    pthread_join(threads[i], NULL);
  }

  free(threads);
  return 0;
}
