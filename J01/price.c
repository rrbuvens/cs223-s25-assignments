#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   int guess;

   printf("Welcome to the Price is Right!\nEnter a guess to win a luxurious new dishwasher: $");
   scanf("%d", &guess);

   int ai1, ai2, price;

   srand(time(0));

   price = (rand() % 2001) + 3000;
   ai1 = (rand() % 2001) + 3000;
   ai2 = (rand() % 2001) + 3000;

   printf("AI contestant #1 guesses $%d\nAI contestant #2 guesses $%d\n", ai1, ai2);
   printf ("The dishwasher cost $%d\n", price);

   if (guess > price && ai1 > price && ai2 > price) {
      printf("Sorry. No one wins the dishwasher. I'm keeping it.\n");
   }
   else if (guess <= price && ((guess > ai1 && guess > ai2) || (ai1 > price && ai2 > price)
      || (guess > ai1 && ai2 > price) || (guess > ai2 && ai1 > price))) {
      printf("Congratulations! You won the dishwasher!\n");
   }
   else if (ai1 <= price && ((ai1 > guess && ai1 > ai2) || (guess > price && ai2 > price)
      || (ai1 > guess && ai2 > price) || (ai1 > ai2 && guess > price))) {
      printf("AI contestant #1 wins the dishwasher!\n");
   }
   else {
      printf("AI contestant #2 wins the dishwasher!\n");
   }
}

