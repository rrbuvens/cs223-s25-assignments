/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 2/22/2025
 * Description: Takes in a filename, a 2d array of pixels, and the dimensions
 * of that array. Writes the contents of the array to a file with the given
 * name in binary.
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {

}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("File error. Exiting...");
        return;
    }

    fprintf(fp, "P6\n");
    fprintf(fp, "# Created by write_ppm_2d\n");
    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fwrite(&pixels[i][j], sizeof(struct ppm_pixel), 1, fp);
        }
    }

    fclose(fp);
}
