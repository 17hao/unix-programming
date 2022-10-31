#include <stdio.h>
#include <stdlib.h>

typedef char *string;

int main(int argc, char **argv) {
  union {
    int ival;
    double dval;
    char cval;
    string sval;
  } u;
  printf("sizeof u=%ld\n", sizeof(u));
  u.dval = 3.14;
  printf("%d\n", u.ival);
  printf("%f\n", u.dval);
  printf("%c\n", u.cval);
  printf("%s\n", u.sval);
}