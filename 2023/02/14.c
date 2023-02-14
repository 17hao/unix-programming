#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int isReady = 0;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *mythread(void *arg) {
  int sleepSeconds = *((int *)arg);
  pthread_t t = pthread_self();
  printf("threadID=%ld sleep %d seconds\n", t, sleepSeconds);
  sleep((unsigned int)sleepSeconds);

  pthread_mutex_lock(&lock);
  isReady = 1;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&lock);
  printf("threadID=%ld exit\n", t);
}

int main(void) {
  pthread_t t1, t2;
  int n1 = 1, n2 = 3;
  pthread_create(&t1, NULL, mythread, (void *)(&n1));
  pthread_create(&t2, NULL, mythread, (void *)(&n2));

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_lock(&lock);
  while (!isReady) {
    pthread_cond_wait(&cond, &lock);
  }
  pthread_mutex_unlock(&lock);
}