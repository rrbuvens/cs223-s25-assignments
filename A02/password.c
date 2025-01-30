/***************************************************
 * Author: Reagan Buvens
 * Program takes in a password and returns a version in which some letters have been
 * replaced with similar-looking numbers.
 */
#include <stdio.h>
#include <string.h>

int main() {
  char pwrd[2048];
  printf("Enter a word: ");
  scanf("%s", pwrd);
  for (int i = 0; i < strlen(pwrd); i++) {
    if (pwrd[i] == 'e') {
      pwrd[i] = '3';
    }
    else if (pwrd[i] == 'l') {
      pwrd[i] = '1';
    }
    else if (pwrd[i] == 'a') {
      pwrd[i] = '@';
    }
  }
  printf("Your bad password is %s\n", pwrd);
  return 0;
}
