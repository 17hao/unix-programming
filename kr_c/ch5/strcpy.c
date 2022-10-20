// section 5.5
// strcpy: copy t to s

#include <malloc.h>
#include <stdio.h>

// array version
void strcpyV1(char *s, char *t) {
  int i = 0;
  while ((s[i] = t[i]) != '\0') {
    i++;
  }
}

// pointer version
void strcpyV2(char *s, char *t) {
  while ((*s++ = *t++) != '\0') {
  }
}

void strcpyV3(char *s, char *t) {
  while ((*s++ = *t++)) {
  }
}

int main(int argc, char **argv) {
  char *s = malloc(sizeof(char) * 16);
  char *t = "hello";
  strcpyV3(s, t);
  printf("%s\n", s);
}