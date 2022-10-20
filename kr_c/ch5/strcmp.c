// secion 5.5
// strcmp: return <0 is s<t, 0 if s==t, >0 if s>t

#include <stdio.h>

// array version
int strcmpV1(char *s, char *t) {
  int i = 0;
  for (i = 0; s[i] == t[i]; i++) {
    if (s[i] == '\0') {
      return 0;
    }
  }
  return s[i] - t[i];
}

// pointer version
int strcmpV2(char *s, char *t) {
  for (; *s == *t; s++, t++) {
    if (*s == '\0') {
      return 0;
    }
  }
  return *s - *t;
}

int main(int argc, char **argv) {
  char *s = "hello";
  char *t = "world";
  printf("%d\n", strcmpV2(s, t));
}