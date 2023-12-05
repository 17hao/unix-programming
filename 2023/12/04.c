#include <stdio.h>
#include <stdlib.h>

void f1(int *i) {
  *i = 1;
}

struct tmpStruct1 {
  char *id;
};

void f2(struct tmpStruct1 *s) {
  s->id = "f2";
}

void f3(struct tmpStruct1 *s) {
  struct tmpStruct1 *new = malloc(sizeof(struct tmpStruct1));
  new->id = "f3";
  s = new;
}

int main() {
  int i = 0;
  f1(&i);
  printf("[f1] i=%d\n", i);

  struct tmpStruct1 s1 = {.id = "main"};
  f2(&s1);
  printf("[f2] s1.id=%s\n", s1.id);

  struct tmpStruct1 *s2 = malloc(sizeof(struct tmpStruct1));
  s2->id = "main";
  f2(s2);
  printf("[f2] s2.id=%s\n", s2->id);

  struct tmpStruct1 *s3 = malloc(sizeof(struct tmpStruct1));
  s3->id = "main";
  f3(s3);
  printf("[f3] s3.id=%s\n", s3->id);
}