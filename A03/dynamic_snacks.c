/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 02/07/2025
 * Description: Allows the user to input a list of snacks. Uses malloc and free to
 * safely allow for various amounts of snacks.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct Snack {
  char name[32];
  float price;
  int amount;
};

int main() {
  int num;
  struct Snack *snacks = NULL;

  printf("Enter a number of snacks: ");
  scanf("%d", &num);

  snacks = (struct Snack*)malloc(num * sizeof(struct Snack));
  if (snacks == NULL) {
    printf("Allocation error. Exiting..");
    return 0;
  }

  for (int i = 0; i < num; i++) {
    float price;
    int amount;

    printf("Enter a name: ");
    scanf("%s", snacks[i].name);
    printf("Enter a price: ");
    scanf("%f", &price);
    printf("Enter an amount: ");
    scanf("%d", &amount);

    snacks[i].price = price;
    snacks[i].amount = amount;
  }

  printf("Welcome to Dynamic Donna's Snack Bar.\n\n");

  for (int i = 0; i < num; i++) {
    printf("%d) %s\tcost: $%0.2f\tquantity: %d\n", i, snacks[i].name, 
      snacks[i].price, snacks[i].amount);
  }

  free(snacks);

  return 0;
}
