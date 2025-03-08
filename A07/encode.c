/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 03/06/2025
 * Description: Given a secret message and an image, encodes it in the least significant
 * bits of the ppm file.
 ---------------------------------------------*/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include "read_ppm.h"
 #include "write_ppm.h"
 
 int main(int argc, char** argv) {
   if (argc != 2) {
     printf("usage: encode <file.ppm>\n");
     return 0;
   }
 
   int w, h;
   struct ppm_pixel** pixels = read_ppm_2d(argv[1], &w, &h);
   printf("Reading %s with width %d and height %d\n", argv[1], w, h);
   printf("Max number of characters in the image: %d\n", (w*h*3)/8);
 
   char *phrase = (char*) malloc(sizeof(char) * ((w * h * 3) / 8));
   printf("Enter a phrase: ");
   scanf("%s", phrase);
 
   unsigned char *colors = (unsigned char*) malloc(sizeof(unsigned char) * 3 * w * h);
   int p = 0;
   for (int i = 0; i < w; i++) {
     for (int j = 0; j < h; j++) {
       colors[p++] = pixels[i][j].red;
       colors[p++] = pixels[i][j].green;
       colors[p++] = pixels[i][j].blue;
     }
   }
 
   p = 0;
   for (int i = 0; i < strlen(phrase); i++) {
     for (int j = 0; j < 8; j++) {
       int mask = 0x1 << (7 - j);
       int bit = (mask & phrase[i]);
       if (bit == 0) {
         colors[p] &= ~(0x1);
       }
       else {
         colors[p] |= 0x1;
       }
       p++;
     }
   }
 
   //reassign pixels array to vals from colors
   p = 0;
   for (int i = 0; i < w; i++) {
     for (int j = 0; j < h; j++) {
       pixels[i][j].red = colors[p++];
       pixels[i][j].green = colors[p++];
       pixels[i][j].blue = colors[p++];
     }
   }
 
   //write pixels array to new file
   char *file = malloc(sizeof(char) * strlen(argv[1]) + strlen("-encoded") + 1);
   strncpy(file, argv[1], strlen(argv[1]) - 4);
   file[strlen(argv[1]) - 4] = '\0';
   write_ppm_2d(strcat(file, "-encoded.ppm"), pixels, w, h);
   printf("Writing file %s\n", file);
 
   //free pixels and colors
   for (int i = 0; i < w; i++) {
     free(pixels[i]);
   }
   free(pixels);
   free(colors);
   free(phrase);
   free(file);
 
   return 0;
 }
 