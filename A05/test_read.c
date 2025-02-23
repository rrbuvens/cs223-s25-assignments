/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 2/22/2025
 * Description: Tests our read_ppm_2d method by feeding it a file and
 * printing the resulting array of pixels.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel** pixels = read_ppm_2d("feep-raw.ppm", &w, &h);

  //print pixels from the file
  printf("Testing file feep-raw.ppm: %d %d\n", w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%u, %u, %u) ", pixels[i][j].red, pixels[i][j].green, pixels[i][j].blue);
    }
    printf("\n");
  }

  for (int i = 0; i < h; i++) {
    free(pixels[i]);
  }
  free(pixels);
  return 0;
}

