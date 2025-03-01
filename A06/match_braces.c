#include <stdio.h>
#include <stdlib.h>

struct brace {
  char data;
  int line;
  int column;
  struct brace* next;
};

struct brace* push(char data, int line, int column, struct brace* stack) {
  struct brace* top = (struct brace*) malloc(sizeof(struct brace));
  if (!top) {
    printf("Memory allocation error. Exiting...");
    exit(1);
  }
  top->data = data;
  top->line = line;
  top->column = column;
  top->next = stack;
  return top;
}

struct brace* pop(struct brace* popped, struct brace* stack) {
  if (stack) {
    struct brace* temp = stack;
    stack = stack->next;
    *popped = *temp;
    free(temp);
    return stack;
  }
  else {
    printf("Nothing to pop.");
    return NULL;
  }
}

void clearStack(struct brace* stack) {
  while (stack) {
    struct brace* temp = stack;
    stack = stack->next;
    free(temp);
  }
}

void printStack(struct brace* stack) {
  struct brace* ptr = stack;
  int n = 0;
  while (ptr) {
    printf("%d) char:%c\tline: %d\tcolumn: %d\n", n, ptr->data, ptr->line, ptr->column);
    ptr = ptr->next;
    n++;
  }
}

int main()
{
  

  return 0;
}

