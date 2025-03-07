/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 03/05/2025
 * Description: Given a ppm file, decodes any possible message which might be hiding
 * in the least significant bits.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  int w, h;
  struct ppm_pixel** pixels = read_ppm_2d(argv[1], &w, &h);
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);
  printf("Max number of characters in the image: %d\n", (w*h*3)/8);

  unsigned char *colors = (unsigned char*) malloc(sizeof(unsigned char) * 3 * w * h);
  int p = 0;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      colors[p++] = pixels[i][j].red;
      colors[p++] = pixels[i][j].green;
      colors[p++] = pixels[i][j].blue;
    }
  }

  unsigned char curr = 0;
  for (int i = 0; i < w * h * 3; i++) {
    curr += ((0x1 & colors[i]) << (7 - (i % 8)));
    if ((i + 1) % 8 == 0) {
      if (curr == '\0') { break; }
      else { 
        printf("%c", curr);
        curr = 0;
      }
    }
  }

  for (int i = 0; i < w; i++) {
    free(pixels[i]);
  }
  free(pixels);
  free(colors);

  return 0;
}

