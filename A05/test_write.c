/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 2/22/2025
 * Description: Tests method write_ppm_2d by reading in a ppm file, then writing
 * it to a new file, then reading that file and printing the contents.
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  struct ppm_pixel** pixels = read_ppm_2d("feep-raw.ppm", &w, &h);
  write_ppm_2d("test.ppm", pixels, w, h);
  struct ppm_pixel** newpixels = read_ppm_2d("test.ppm", &w, &h);

  printf("Testing file test.ppm: %d %d\n", w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%u, %u, %u) ", pixels[i][j].red, pixels[i][j].green, pixels[i][j].blue);
    }
    printf("\n");
  }

  for (int i = 0; i < h; i++) {
    free(pixels[i]);
    free(newpixels[i]);
  }
  free(pixels);
  free(newpixels);
  return 0;
}
