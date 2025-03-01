/**
 * Name: Reagan Buvens
 * Date: 3/1/2025
 * Description: Reads in a given list of files, then allows user to input commands.
 * If given a filename, lists the dependencies of that file.
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "tree.h"

void dependencies(char* filename) {
  FILE *fp = fopen(filename, "r");
  char line[128];
  printf("%s has the following dependencies\n", filename);

  while (fgets(line, sizeof(line), fp)) {
    if (strstr(line, "#include")) {
      char file[32];
      int offset = strlen("#include <");
      strncpy(file, line + offset, strlen(line) - offset - 3);
      file[strlen(line) - offset - 3] = '\0';
      printf("  %s\n", file);
    }
  }

  fclose(fp);
}

int main(int argc, char* argv[]) {
  struct tree_node* files = NULL;
  clock_t start = clock();
  printf("Processing %d files\n", argc - 1);
  for (int i = 1; i < argc; i++) {
    if (access(argv[i], R_OK) == 0) {
      files = insert(argv[i], files);
    }
  }
  clock_t end = clock();
  printf("Time elapsed: %f\n", ((double)end - start)/CLOCKS_PER_SEC);

  printf("Allowed commands: quit, list, or <filename>\n");
  char input[32];
  scanf("%s", input);

  while (strcmp(input, "quit") != 0) {
    if (strcmp(input, "list") == 0) {
      printSorted(files);
    }
    else {
      struct tree_node* file = find(input, files);
      if (!file) {
        printf("%s not found\n", input);
      }
      else {
        dependencies(input);
      }
    }
    scanf("%s", input);
  }

  clear(files);
  return 0;
}
