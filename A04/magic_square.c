/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 02/11/2025
 * Description: Given a square matrix of integers, determines whether that
 * matrix qualifies as a magic square.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int main() {
  int rows, cols;
  scanf("%d", &rows);
  scanf(" %d", &cols);

  int** magic = malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    magic[i] = malloc(sizeof(int) * cols);
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      scanf(" %d", &magic[i][j]);
    }
  }

  int number = 0;
  for (int i = 0; i < rows; i++) { number += magic[i][0]; } //find sum of first column

  int isMagic = 1; //start as true, update later if proven wrong

  //check all rows and columns
  for (int i = 0; i < rows; i++) {
    int sumrow = 0;
    int sumcol = 0;
    for (int j = 0; j < cols; j++) {
      sumrow += magic[i][j];
      sumcol += magic[j][i];
    }
    if (sumrow != number || sumcol != number) {
      isMagic = 0;
      break;
    }
  }

  //check diagonals
  int sumleft = 0;
  int sumright = 0;
  for (int i = 0; i < rows; i++) {
    sumleft += magic[i][i];
    sumright += magic[i][rows - i - 1];
  }
  if (sumleft != number || sumright != number) { isMagic = 0; }

  if (isMagic == 1) {
    printf("M is a magic square (magic constant = %d)\n", number);
  }
  else {
    printf("M is NOT a magic square\n");
  }

  for (int i = 0; i < rows; i++) {
    free(magic[i]);
  }
  free(magic);

  return 0;
}
