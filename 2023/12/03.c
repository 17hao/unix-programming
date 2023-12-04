#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct base {
  int id;
};

struct seller {
  struct base base;
  char *name;
};

struct customer {
  struct base base;
  char *location;
};

struct keyboard {
  char *brand;
  char *layout;
  char *owner;
};

void f1(struct base *s) {
  printf("seller's id=%d\n", s->id);
}

void f2(struct keyboard *k, char **buf) {
  memcpy(*buf, k, sizeof(struct keyboard));
}

void f3(char **buf, struct keyboard *new) {
  memcpy(new, *buf, sizeof(struct keyboard));
  new->owner = "f3";
}

int main() {
  struct seller s = {.base = {.id = 1}, .name = "s1"};
  f1((struct base *)&s);

  struct keyboard k = {.brand = "HHKB", .layout = "en_us", .owner = "main"};
  char *buf = malloc(sizeof(struct keyboard));
  f2(&k, &buf);
  struct keyboard new;
  f3(&buf, &new);
  printf("keyboard's owner=%s\n", new.owner);
}