/**
 * Name: Reagan Buvens
 * Date: 04/18/2025
 * Descripton: Creates and consumes int values in an infinite loop using two threads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

struct data {
  int queue[N];
  int start;
  int out;
  int amt;
  pthread_mutex_t mutex;
  pthread_cond_t notEmpty;
  pthread_cond_t notFull;
};

int produce_item() {
  return rand() % 10;
}

void consume_item(int item) {
  printf("Received item: %d\n", item);
}

void *produce(void *arg) {
  struct data* args = (struct data*) arg;
  while(1) {
    pthread_mutex_lock(&(args->mutex));
    while(args->amt == N) {
      pthread_cond_wait(&(args->notFull), &(args->mutex));
    }

    args->queue[args->start] = produce_item();
    args->start = (args->start + 1) % N;
    args->amt++;

    pthread_cond_signal(&(args->notEmpty));
    pthread_mutex_unlock(&(args->mutex));

    sleep(1);
  }
  return NULL;
}

void *consume(void *arg) {
  struct data* args = (struct data*) arg;
  while(1) {
    pthread_mutex_lock(&(args->mutex));
    while(args->amt == 0) {
      pthread_cond_wait(&(args->notEmpty), &(args->mutex));
    }

    consume_item(args->queue[args->out]);
    args->out = (args->out + 1) % N;
    args->amt--;

    pthread_cond_signal(&(args->notFull));
    pthread_mutex_unlock(&(args->mutex));

    sleep(1);
  }
  return NULL;
}

int main() {
  srand(time(NULL));

  pthread_t threads[2];

  struct data args;
  args.start = 0;
  args.out = 0;
  args.amt = 0;
  pthread_mutex_init(&(args.mutex), NULL);
  pthread_cond_init(&(args.notEmpty), NULL);
  pthread_cond_init(&(args.notFull), NULL);

  pthread_create(&threads[0], NULL, produce, &args);
  pthread_create(&threads[1], NULL, consume, &args);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  
  return 0;
}