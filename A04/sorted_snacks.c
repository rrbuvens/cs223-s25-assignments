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
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int amount;
  struct snack* next;
};

struct snack* insert_first(char* name, float cost, int amount, struct snack* list){
  struct snack* s = (struct snack*) malloc(sizeof(struct snack));
  if (s == NULL) {
    printf("Allocation error. Exiting...");
    exit(1);
  }
  strcpy(s->name, name);
  s->cost = cost;
  s->amount = amount;
  s->next = list;
  return s;
}

void clear(struct snack* list) {
  struct snack* ptr = list;
  while (ptr != NULL) {
    struct snack* temp = ptr;
    ptr = ptr->next;
    free(temp);
  }
  list = NULL;
}

void printList(struct snack* list) {
  struct snack* ptr = list;
  int i = 0;
  while (ptr != NULL) {
    printf("%d) %s\tcost: $%.02f\tquantity: %d\n", i, ptr->name, ptr->cost, ptr->amount);
    ptr = ptr->next;
    i++;
  }
}

struct snack* sortName(struct snack* list) {
  for (struct snack* head = list; head != NULL; head = head->next) {
    struct snack* min = head;

    for (struct snack* ptr = head->next; ptr != NULL; ptr = ptr->next) {
      if (strcmp(ptr->name, min->name) < 0) {
        min = ptr;
      }
    }

    if (min != head) {
      char tname[32];
      strcpy(tname, head->name);
      float tcost = head->cost;
      int tamount = head->amount;

      strcpy(head->name, min->name);
      head->cost = min->cost;
      head->amount = min->amount;

      strcpy(min->name, tname);
      min->cost = tcost;
      min->amount = tamount;
    }
  }

  return list;
}

struct snack* sortCost(struct snack* list) {
  for (struct snack* head = list; head != NULL; head = head->next) {
    struct snack* min = head;

    for (struct snack* ptr = head->next; ptr != NULL; ptr = ptr->next) {
      if (ptr->cost < min->cost) {
        min = ptr;
      }
    }

    if (min != head) {
      char tname[32];
      strcpy(tname, head->name);
      float tcost = head->cost;
      int tamount = head->amount;

      strcpy(head->name, min->name);
      head->cost = min->cost;
      head->amount = min->amount;

      strcpy(min->name, tname);
      min->cost = tcost;
      min->amount = tamount;
    }
  }

  return list;
}

struct snack* sortQuantity(struct snack* list) {
  for (struct snack* head = list; head != NULL; head = head->next) {
    struct snack* min = head;

    for (struct snack* ptr = head->next; ptr != NULL; ptr = ptr->next) {
      if (ptr->amount < min->amount) {
        min = ptr;
      }
    }

    if (min != head) {
      char tname[32];
      strcpy(tname, head->name);
      float tcost = head->cost;
      int tamount = head->amount;

      strcpy(head->name, min->name);
      head->cost = min->cost;
      head->amount = min->amount;

      strcpy(min->name, tname);
      min->cost = tcost;
      min->amount = tamount;
    }
  }

  return list;
}

int main() {
  int num;

  printf("Enter a number of snacks: ");
  scanf("%d", &num);

  struct snack* snacks = NULL;

  for (int i = 0; i < num; i++) {
    char name[32];
    float cost;
    int amount;

    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a cost: ");
    scanf("%f", &cost);
    printf("Enter an amount: ");
    scanf("%d", &amount);

    snacks = insert_first(name, cost, amount, snacks);
  }

  printf("\nWelcome to Sorted Sally's Snack Bar!\n\n");

  snacks = sortName(snacks);
  printList(snacks);

  clear(snacks);
}
