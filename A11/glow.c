/**
 * Name: Reagan Buvens
 * Date: 04/11/2025
 * Description: Implements a program which takes a ppm image and make the brightest parts
 * appear to glow.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  int w;
  int h;
  struct ppm_pixel **orig = read_ppm_2d("earth-small.ppm", &w, &h);
  struct ppm_pixel **bright = malloc(sizeof(struct ppm_pixel*) * h);
  struct ppm_pixel **blur = malloc(sizeof(struct ppm_pixel*) * h);
  for (int i = 0; i < h; i++) {
    bright[i] = malloc(sizeof(struct ppm_pixel) * w);
    blur[i] = malloc(sizeof(struct ppm_pixel) * w);
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel curr = orig[i][j];
      unsigned char brightness = (curr.red + curr.green + curr.blue)/3;
      if (brightness > 200) {
        bright[i][j] = orig[i][j];
      }
      else {
        bright[i][j].red = 0;
        bright[i][j].green = 0;
        bright[i][j].blue = 0;
      }
    }
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int red = 0;
      int green = 0;
      int blue = 0;
      for (int x = i - 2; x < i + 3; x++) {
        for (int y = j - 2; y < j + 3; y++) {
          if (x >= 0 && x < h && y >= 0 && y < w) {
            red += bright[x][y].red;
            green += bright[x][y].green;
            blue += bright[x][y].blue;
          }
        }
      }

      blur[i][j].red = (unsigned char) (red/25);
      blur[i][j].green = (unsigned char) (green/25);
      blur[i][j].blue = (unsigned char) (blue/25);

      int r = orig[i][j].red + blur[i][j].red;
      orig[i][j].red = r > 255 ? 255 : r;
      int g = orig[i][j].green + blur[i][j].green;
      orig[i][j].green = g > 255 ? 255 : g;
      int b = orig[i][j].blue + blur[i][j].blue;
      orig[i][j].blue = b > 255 ? 255 : b;
    }
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
}
