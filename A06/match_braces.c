/**
 * Name: Reagan Buvens
 * Date: 02/28/2025
 * Description: Given an input file, checks that all braces are matched.
 */

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
    printf("Memory allocation error. Exiting...\n");
    exit(1);
  }
  top->data = data;
  top->line = line;
  top->column = column;
  top->next = stack;
  return top;
}

struct brace* pop(struct brace** popped, struct brace* stack) {
  if (stack) {
    *popped = stack;
    stack = stack->next;
    return stack;
  }
  else {
    *popped = NULL;
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

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("usage: ./match_braces input_file\n");
    exit(1);
  }

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    printf("File error. Exiting...\n");
    exit(1);
  }

  char ch = fgetc(fp);
  int l = 1;
  int c = 0;
  struct brace* braces = NULL;
  while(ch != EOF) {
    if (ch == '{') {
      braces = push(ch, l, c, braces);
    }
    else if (ch == '}') {
      struct brace* popped = NULL;
      braces = pop(&popped, braces);
      if (!popped) {
        printf("Unmatched brace on Line %d and Column %d\n", l, c);
      }
      else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", popped->line, popped->column, l, c);
        free(popped);
      }
    }
    else if (ch == '\n') {
      l++;
      c = 0;
    }
    c++;
    ch = fgetc(fp);
  }

  while (braces) {
    struct brace* popped = NULL;
    braces = pop(&popped, braces);
    printf("Unmatched brace on Line %d and Column %d\n", popped->line, popped->column);
    free(popped);
  }

  fclose(fp);
  clearStack(braces);

  return 0;
}

