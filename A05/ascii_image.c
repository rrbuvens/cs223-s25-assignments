/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 2/22/2025
 * Description: Converts a ppm file into an ascii image.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

char** asciiConvert(struct ppm_pixel** pixels, int w, int h) {
  char** ascii = malloc(sizeof(char*) * h);
  if (!ascii) {
    printf("Memory allocation error. Exiting...");
    return NULL;
  }
  for (int i = 0; i < h; i++) {
    ascii[i] = malloc(sizeof(char) * w);
    if (!ascii[i]) {
      printf("Memory allocation error. Exiting...");
      return NULL;
    }
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel curr = pixels[i][j];
      int intensity = (curr.red + curr.green + curr.blue) / 3;
      if (intensity < 26) { ascii[i][j] = '@'; }
      else if (intensity < 51) { ascii[i][j] = '#'; }
      else if (intensity < 76) { ascii[i][j] = '%'; }
      else if (intensity < 101) { ascii[i][j] = '*'; }
      else if (intensity < 126) { ascii[i][j] = 'o'; }
      else if (intensity < 151) { ascii[i][j] = ';'; }
      else if (intensity < 176) { ascii[i][j] = ':'; }
      else if (intensity < 201) { ascii[i][j] = ','; }
      else if (intensity < 226) { ascii[i][j] = '.'; }
      else { ascii[i][j] = ' '; }
    }
  }

  return ascii;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("No filename given.");
    return 0;
  }

  int w, h;
  struct ppm_pixel** pixels = read_ppm_2d(argv[1], &w, &h);
  if (!pixels) {
    printf("File read error. Exiting...");
    return 0;
  }

  char** ascii = asciiConvert(pixels, w, h);
  if (!ascii) {
    printf("Conversion error. Exiting...");
    return 0;
  }

  printf("Reading file %s with width %d and height %d\n", argv[1], w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("%c", ascii[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < h; i++) {
    free(pixels[i]);
    free(ascii[i]);
  }
  free(pixels);
  free(ascii);

  return 0;
}
