#include <stdio.h>
#include <string.h>

int main()
{
   char digits[32];

   printf("Enter digits: ");
   scanf("%s", digits);

   int sorted[10];
   for (int i = 0; i < 10; i++) {
      sorted[i] = 0;
   }

   for (int i = 0; i < strlen(digits); i++) {
      if (digits[i] >= '0' && digits[i] <= '9') {
         sorted[digits[i] - '0'] += 1;
      }
   }

   for (int i = 0 ; i < 10; i++) {
      for (int j = 0; j < sorted[i]; j++) {
         printf("%d ", i);
      }
   }
}
