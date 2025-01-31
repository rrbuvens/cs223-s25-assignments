/***************************************************
 * Author: Reagan Buvens
 * Date: 01/31/2025
 * Functions as a Caesar cypher. Allows the user to input a word to be encrypted
 * and an amount by which to shift each letter, then outputs encrypted result.
 */
#include <stdio.h>
#include <string.h>

char* cypher(char* word, int shift) {

  for (int i = 0; i < strlen(word); i++) {
    if (word[i] + shift > 'z') {
      int over = word[i] + shift - 'z';
      word[i] = 'a' + over - 1;
    }
    else if (word[i] + shift < 'a') {
      int under = 'a' - word[i] - shift;
      word[i] = 'z' - under + 1;
    }
    else {
      word[i] += shift;
    }
  }
  
  return word;
}

int main() {
  char word[2048];
  int shift;

  printf("Enter a word: ");
  scanf("%s", word);
  printf("Enter a shift: ");
  scanf("%d", &shift);
  printf("Your cypher is %s\n", cypher(word, shift));

  return 0;
}
