/***************************************************
 * Author: Reagan Buvens
 * Creates and stores a list of snacks, allowing the user to input an amount of money
 * and request a snack. Responds according to the snack.
 */
#include <stdio.h>

struct Snack {
  char* name;
  float price;
  int amount;
};

int main() {
  struct Snack snacks[3];

  snacks[0].name = "Skittles";
  snacks[0].price = 3.50;
  snacks[0].amount = 10;

  snacks[1].name = "Cheez-its";
  snacks[1].price = 2.50;
  snacks[1].amount = 3;

  snacks[2].name = "Hummus";
  snacks[2].price = 4.75;
  snacks[2].amount = 0;

  float money;
  int choice;

  printf("Welcome to Steven Struct's Snack Bar.\n\nHow much money do you have? $");
  scanf("%f", &money);

  for (int i = 0; i < 3; i++) {
    printf("\n%d) %s\tcost: $%0.2f\tquantity: %d", i, snacks[i].name, 
      snacks[i].price, snacks[i].amount);
  }

  printf("\n\nWhat snack would you like to buy? [0, 1, 2] ");
  scanf("%d", &choice);

  if (choice < 0 || choice > 2) {
    printf("Sorry, that's not on the list. :(\n");
  }
  else if(snacks[choice].amount == 0) {
    printf("Sorry, we are out of %s.\n", snacks[choice].name);
  }
  else if (snacks[choice].price > money) {
    printf("You can't afford it!\n");
  }
  else {
    printf("You bought %s.\nYou have $%0.2f left.\n", snacks[choice].name, 
      money - snacks[choice].price);
  }
}
