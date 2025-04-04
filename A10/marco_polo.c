/**
 * Name: Reagan Buvens
 * Date: 04/04/2025
 * Description: Creates a parent and a child process, which call and respond to each
 * other.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void marco_handler(int sig) {
  if (sig == SIGALRM) {
    printf("Marco\n");
    kill(getppid(), SIGALRM);
  }
  else if (sig == SIGTERM) {
    exit(0);
  }
}

void polo_handler(int sig) {
  if (sig == SIGALRM) {
    printf("Polo\n");
  }
}

int main()
{
  signal(SIGALRM, polo_handler);
  int ret = fork();

  if (ret == 0) {
    signal(SIGALRM, marco_handler);
    signal(SIGTERM, marco_handler);
    while(1);
  }
  else {
    char input;
    
    while (1) {
      input = getchar();
      if (input == 'm') {
        kill(ret, SIGALRM);
      }
      else if (input == 'q') {
        kill(ret, SIGTERM);
        break;
      }
    }
  }
  return 0;
}
