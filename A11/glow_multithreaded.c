#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct glow_args {
  int start;
  int end;
  int w;
  int h;
  int blursize;
  int threshold;
  struct ppm_pixel **orig;
  struct ppm_pixel **bright;
  struct ppm_pixel **blur;
};

void *glow(void *arg) {
  struct glow_args* args = (struct glow_args*) arg;

  printf("Thread sub-image slice: rows (%d, %d)\n", args->start, args->end);

  for (int i = args->start; i < args->end; i++) {
    for (int j = 0; j < args->w; j++) {
      struct ppm_pixel curr = args->orig[i][j];
      int brightness = (curr.red + curr.green + curr.blue) / 3;

      if (brightness > args->threshold) {
        args->bright[i][j] = curr;
      } 
      else {
        args->bright[i][j] = (struct ppm_pixel){0, 0, 0};
      }
    }
  }

  int half = args->blursize / 2;
  for (int i = args->start; i < args->end; i++) {
    for (int j = 0; j < args->w; j++) {
      int red = 0; 
      int green = 0; 
      int blue = 0; 
      int count = 0;

      for (int x = i - half; x <= i + half; x++) {
        for (int y = j - half; y <= j + half; y++) {
          if (x >= 0 && x < args->h && y >= 0 && y < args->w) {
            red += args->bright[x][y].red;
            green += args->bright[x][y].green;
            blue += args->bright[x][y].blue;
            count++;
          }
        }
      }
      args->blur[i][j].red = red / count;
      args->blur[i][j].green = green / count;
      args->blur[i][j].blue = blue / count;

      int r = args->orig[i][j].red + args->blur[i][j].red;
      int g = args->orig[i][j].green + args->blur[i][j].green;
      int b = args->orig[i][j].blue + args->blur[i][j].blue;

      args->orig[i][j].red = r > 255 ? 255 : r;
      args->orig[i][j].green = g > 255 ? 255 : g;
      args->orig[i][j].blue = b > 255 ? 255 : b;
    }
  }
  free(arg); 
  return NULL;
}

int main(int argc, char* argv[]) 
{
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': N = atoi(optarg); break;
      case 't': threshold = atoi(optarg); break;
      case 'b': blursize = atoi(optarg); break;
      case 'f': filename = optarg; break;
      case '?': printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); break;
    }
  }

  int w, h;
  struct ppm_pixel **orig = read_ppm_2d(filename, &w, &h);
  struct ppm_pixel **bright = malloc(sizeof(struct ppm_pixel*) * h);
  struct ppm_pixel **blur = malloc(sizeof(struct ppm_pixel*) * h);
  for (int i = 0; i < h; i++) {
    bright[i] = malloc(sizeof(struct ppm_pixel) * w);
    blur[i] = malloc(sizeof(struct ppm_pixel) * w);
    memset(bright[i], 0, sizeof(struct ppm_pixel) * w);
    memset(blur[i], 0, sizeof(struct ppm_pixel) * w);
  }

  pthread_t *threads = malloc(sizeof(pthread_t) * N);
  int numRows = h/N;

  for (int i = 0; i < N; i++) {
    struct glow_args* args = malloc(sizeof(struct glow_args));
    args->start = i * numRows;
    args->end = (i == N - 1) ? h : (i + 1) * numRows;
    args->w = w;
    args->h = h;
    args->blursize = blursize;
    args->threshold = threshold;
    args->orig = orig;
    args->bright = bright;
    args->blur = blur;

    pthread_create(&threads[i], NULL, glow, (void *) args);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm_2d("glow.ppm", orig, w, h);

  for (int i = 0; i < h; i++) {
    free(orig[i]);
    free(bright[i]);
    free(blur[i]);
  }
  free(orig);
  free(bright);
  free(blur);
  free(threads); 

  return 0;
}