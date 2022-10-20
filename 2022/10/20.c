#include <stdio.h>

int main(int argc, char **argv) {
  int i;
  printf("%d\n", i);

  short s;
  printf("%d\n", s);

  struct node {
    struct node *next;
    int val;
  };

  struct node n1 = {0, 1};
  struct node n2 = {0, 2};
  struct node *head = &n1;
  head->next = &n2;

  struct {
    int x;
    int y;
  } p1, p2;

  p1.x = 1;
  p2.y = 2;

  printf("p1.x=%d\n", p1.x);
  printf("p1.y=%d\n", p1.y);
}