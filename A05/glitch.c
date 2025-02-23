/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 2/22/2025
 * Description: Changes the color values of each pixel in a given image to
 * make it appear that a glitch has occurred.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

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

  //shift all pixels
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel curr = pixels[i][j];
      curr.red = curr.red << (rand() % 2);
      curr.green = curr.green << (rand() % 2);
      curr.blue = curr.blue << (rand() % 2);
      pixels[i][j] = curr;
    }
  }

  char* filename = malloc(strlen(argv[1]) + 8);
  for (int i = 0; i < strlen(argv[1]) - 4; i++) {
    filename[i] = argv[1][i];
  }
  filename[strlen(argv[1]) - 4] = '\0';
  strcat(filename, "-glitch.ppm");
  write_ppm_2d(filename, pixels, w, h);

  for (int i = 0; i < h; i++) {
    free(pixels[i]);
  }
  free(pixels);
  free(filename);

  return 0;
}
