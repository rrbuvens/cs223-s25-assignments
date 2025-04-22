#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int sig) {
  printf("Help! I've been shot!\n");
  exit(1);
}

int main()
{
  signal(SIGINT, sigint_handler);
  while(1);
  return 0;
}
