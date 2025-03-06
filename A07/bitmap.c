/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 03/05/2025
 * Description: Given a 64-bit unsigned integer, produces an 8x8 ascii image
 * representing each bit of the integer.
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

  for (int i = 63; i >= 0; i--) {
    unsigned long mask = 0x1ul << i;
    int bit = (mask & img) >> i;
    if (bit) {
      printf("@ ");
    }
    else {
      printf("  ");
    }
    if (i % 8 == 0) {
      printf("\n");
    }
  }
  return 0;
}
