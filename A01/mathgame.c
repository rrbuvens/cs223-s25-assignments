/***************************************************
 * mathgame.c
 * Author: Reagan Buvens
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Welcome to Math Game!\nHow many rounds do you want to play? ");
  int num, sum = 0;
  scanf("%d", &num);
  for (int i = 0; i < num; i++) {
    int a = (rand() % 9) + 1;
    int b = (rand() % 9) + 1;
    int ans;
    printf("\n\n%d + %d = ? ", a, b);
    scanf("%d", &ans);
    if (ans == a + b) {
      sum++;
      printf("Correct!");
    }
    else {
      printf("Incorrect :(");
    }
  }
  printf("You answered %d/%d correctly.", sum, num);
  return 0;
}
