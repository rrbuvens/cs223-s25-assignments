/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 02/07/2025
 * Description: Allows the user to input a length n and width m, then creates a
 * nxm board and randomly places a wampus on the board. All other cells show
 * how far away the wampus is.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int row, col, wrow, wcol;

  printf("Number of rows: ");
  scanf("%d", &row);
  printf("Number of columns: ");
  scanf("%d", &col);

  srand(time(0));

  wrow = rand() % row;
  wcol = rand() % col;

  char** board = malloc(sizeof(char*) * row);
  for (int i = 0; i < row; i++) {
    board[i] = malloc(sizeof(char) * col);
  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (i == wrow && j == wcol) { board[i][j] = 'W'; }
      else { board[i][j] = abs(i - wrow) + abs (j - wcol) + '0'; }
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < row; i++) {
    free(board[i]);
  }
  free(board);
  return 0;
}
