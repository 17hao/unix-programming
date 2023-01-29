// volume1 p626
// Creating a new thread and join with it.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *threadFunc(void *args) {
  char *s = (char *)args;
  printf("[threadID=%ld] %s\n", pthread_self(), s);
  return (void *)strlen(s);
}

int main(void) {
  pthread_t thread;
  int s = pthread_create(&thread, NULL, threadFunc, "Hello, world!");
  if (s < 0) {
    // TODO errno
    exit(EXIT_FAILURE);
  }

  printf("Message from main thread\n");

  void *res;
  pthread_join(thread, &res);
  printf("Thread returned %ld\n", (long)res);
}