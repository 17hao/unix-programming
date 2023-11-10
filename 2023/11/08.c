#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char src[] = "hello, world";
  size_t len = strlen(src);
  printf("strlen(src)=%ld\tsizeof(src)=%ld\n", len, sizeof(src));
  char *dst = malloc(sizeof(char) * len);
  if (dst == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  strcpy(dst, src);
  printf("%s\n", dst);
}