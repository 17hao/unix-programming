#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  time_t timestamp = time(NULL);
  printf("%ld\n", timestamp);

  srand(timestamp);
  int n = rand();
  printf("RAND_MAX=%d\n", RAND_MAX);
  printf("%d\n", n);
}