/*----------------------------------------------
 * Author: Reagan Buvens
 * Date: 02/11/2025
 * Description: Allows the user to input a number of snacks, then uses a singly-linked
 * list to store those snacks. Implements three methods to sort the list, one method
 * to insert snacks at the beginning of the list, one method to clear and free
 * the list, and one method to print the list.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct snack {
  char* name;
  float cost;
  int amount;
  struct snack* next;
};

struct snack* insert_first(char* name, float cost, int amount, struct snack* list){
  struct snack* s = malloc(sizeof(struct snack));
  if (s == NULL) {
    printf("Allocation error. Exiting...");
    exit(1);
  }
  s->name = name;
  s->cost = cost;
  s->amount = amount;
  s->next = list;
  return s;
}

void clear(struct snack* list) {
  struct snack* nextFree = list->next;
  while (list != NULL) {
    free(&list);
    list = nextFree;
    nextFree = nextFree->next;
  }
}

void printList(struct snack* list) {
  struct snack* ptr = list;
  int i = 0;
  while (ptr != NULL) {
    printf("%d) %s\tcost: $%.02f\tquantity: %d", i, ptr->name, ptr->cost, ptr->amount);
    ptr = ptr->next;
  }
}

struct snack* sortCost(struct snack* list) {
  struct snack* head = list;
  struct snack* ptr = list;

  

  return NULL;
}

struct snack* sortName(struct snack* list) {
  return NULL;
}

struct snack* sortQuantity(struct snack* list) {
  return NULL;
}

int main() {
  int num;

  printf("Enter a number of snacks: ");
  scanf("%d", &num);

  struct snack* snacks;

  for (int i = 0; i < num; i++) {
    char* name;
    float cost;
    int amount;

    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a cost: ");
    scanf("%f", &cost);
    printf("Enter an amount: ");
    scanf("%d", &amount);

    insert_first(name, cost, amount, snacks);
  }

  printf("\nWelcome to Sorted Sally's Snack Bar!");

  //print out snacks in alphabetical order

  clear(snacks);
}
