/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 02/22/2025
 * Description: Reads a given .ppm file into a 2d array of pixels, then returns that 
 * array.
 ---------------------------------------------*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "read_ppm.h"
 
 // Choose *one* to implement (do not remove the other one!)
 
 struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    return NULL;
  }
 
 struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
      printf("Invalid filename. Exiting...");
      return NULL;
    }
  
    char line[256];
  
    fgets(line, 256, fp); //read line with "P6"
    fgets(line, 256, fp); //read comment line
    fgets(line, 256, fp); //read line with width and height
  
    char num[32];
    strcpy(num, strtok(line, " ")); //tokenize width parameter
    *w = atoi(num);
    strcpy(num, strtok(NULL, " ")); //tokenize height parameter
    *h = atoi(num);
 
    fgets(line, 256, fp); //read line with maxval
  
    //malloc space for 2d array
    struct ppm_pixel** image = (struct ppm_pixel**) malloc(sizeof(struct ppm_pixel*) * *h);
    if (!image) {
      printf("Memory allocation error. Exiting...");
      return NULL;
    }
    for (int i = 0; i < *h; i++) {
      image[i] = (struct ppm_pixel*) malloc(sizeof(struct ppm_pixel) * *w);
      if (!image[i]) {
        printf("Memory allocation error. Exiting...");
        return NULL;
    
      }
    }
  
    //read in pixels from ppm file
    for (int i = 0; i < *h; i++) {
      for (int j = 0; j < *w; j++) {
        fread(&image[i][j], sizeof(struct ppm_pixel), 1, fp);
      }
    }
  
    fclose(fp);
    return image;
 } 