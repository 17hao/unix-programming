#include <stdio.h>
#include <stdlib.h>

#define k1 1
#define k2 2
#define k3 3

typedef unsigned long uint64;

int main(int argc, char **argv) {
  char *map[] = {
      [k1] "v1",
      [k2] "v2",
  };
  char *v1 = map[k1];
  printf("%s\n", v1);

  char *strings[3];
  // char **strings;
  // strings = malloc(sizeof(char*) * 3);
  strings[0] = "a";
  strings[1] = "b";
  for (int i = 0; i < 2; i++) {
    printf("%s\n", strings[i]);
  }
}