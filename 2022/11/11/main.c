#include <stdio.h>

#include "queue.h"
#include "stack.h"

int main(void) {
#ifdef FLAG
  printf("FLAG is defined.\n");
#endif

  printf("====== stack ======>>>\n");

  struct stack s = {};
  spush(&s, 1);
  int i = spop(&s);
  printf("%d\n", i);

  spush(&s, 2);
  spush(&s, 3);
  printf("%d\n", spop(&s));

  printf("====== queue ======>>>\n");

  struct Queue q = {.head = 0, .tail = 0};
  qpush(&q, 1);
  printf("%d\n", qpop(&q));

  qpush(&q, 2);
  printf("%d\n", qpop(&q));

  qpush(&q, 3);
  printf("%d\n", qpop(&q));

  qpush(&q, 4);
  printf("%d\n", qpop(&q));

  qpush(&q, 5);
  printf("%d\n", qpop(&q));
}
