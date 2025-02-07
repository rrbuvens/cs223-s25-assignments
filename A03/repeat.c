/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 02/06/2025
 * Description: Takes in a word and a number n, then makes a string which
 * repeats that word n times. If malloc fails, exits the program.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char word[32];
  int count;
  char* repeat = NULL;

  printf("Enter a word: ");
  scanf("%s", word);
  printf("Enter a count: ");
  scanf("%d", &count);

  repeat = malloc(count * strlen(word) + 1);
  if (repeat == NULL) {
    printf("Cannot allocate new string. Exiting...\n");
    return 0;
  }
  repeat[0] = '\0';

  for (int i = 0; i < count; i++) {
    strcat(repeat, word);
  }

  printf("%s\n", repeat);

  free(repeat);

  return 0;
}
