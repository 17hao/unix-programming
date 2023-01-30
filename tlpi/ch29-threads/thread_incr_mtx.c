#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static int glob = 0;

void *threadFunc(void *arg) {
  int loops = *((int *)arg);
  int s;
  for (int i = 0; i < loops; i++) {
    s = pthread_mutex_lock(&mtx);
    if (s < 0) {
      exit(EXIT_FAILURE);
    }
    s = pthread_mutex_trylock(&mtx);
    if (s == EBUSY) {
      printf("pthread_mutex_trylock return EBUSY\n");
    }
    glob++;
    pthread_mutex_unlock(&mtx);
  }
}

int main(int argc, char **argv) {
  pthread_t t1, t2;
  int loops, s;
  int *ploops;

  loops = argc > 1 ? atoi(argv[1]) : 10000000;
  ploops = &loops;
  s = pthread_create(&t1, NULL, threadFunc, (void *)ploops);
  if (s < 0) {
    exit(EXIT_FAILURE);
  }
  s = pthread_create(&t2, NULL, threadFunc, (void *)ploops);
  if (s < 0) {
    exit(EXIT_FAILURE);
  }

  s = pthread_join(t1, NULL);
  if (s < 0) {
    exit(EXIT_FAILURE);
  }
  s = pthread_join(t2, NULL);
  if (s < 0) {
    exit(EXIT_FAILURE);
  }

  printf("glob = %d\n", glob);
}