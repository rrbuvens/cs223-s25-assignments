/***************************************************
 * mathgame.c
 * Author: Reagan Buvens
 * Implements a math game
 */

#include <stdio.h>

int main() {
  printf("Welcome to Math Game!\nHow many rounds do you want to play? \n");
  int num, sum;
  scanf("%d", &num);
  printf("%d", num);
  for (int i = 0; i < num; i++) {
    int a = (rand() % 9) + 1;
    int b = (rand() % 9) + 1;
    int ans;
    printf("\n\n%d + %d = ? ", a, b);
    scanf("%d", &ans);
    if (ans == a + b) {
      sum ++;
      printf("\nCorrect!");
    }
    else {
      printf("\nIncorrect :(");
    }
    printf("You answered %d/%d correctly.", sum, num);
  }
  return 0;
}
