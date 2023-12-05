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

// proper way
void f3(char *buf, struct keyboard *new) {
  memcpy(new, buf, sizeof(struct keyboard));
  new->owner = "f3";
}

// unexpected
void f4(char *buf, struct keyboard *new) {
  new = (struct keyboard *)buf;
  printf("[debug] f4 keyboard's brand=%s\tlayout=%s\n", new->brand, new->layout);
  new->owner = "f4";
}

void f5(char *buf, struct keyboard **new) {
  *new = (struct keyboard *)buf;
  printf("[debug] f5 keyboard's brand=%s\tlayout=%s\n", (*new)->brand, (*new)->layout);
  (*new)->owner = "f5";
}

int main() {
  struct seller s = {.base = {.id = 1}, .name = "s1"};
  f1((struct base *)&s);

  struct keyboard k = {.brand = "HHKB", .layout = "en_us", .owner = "main"};
  char *buf = malloc(sizeof(struct keyboard));
  f2(&k, &buf);

  struct keyboard f3kb;
  f3(buf, &f3kb);
  printf("f3kb's owner=%s\n", f3kb.owner);

  struct keyboard f4kb;
  f4(buf, &f4kb);
  printf("f4kb's brand=%s\n", f4kb.brand);

  struct keyboard *f5kb = malloc(sizeof(struct keyboard));
  f5(buf, &f5kb);
  printf("f5kb's owner=%s\n", f5kb->owner);
}