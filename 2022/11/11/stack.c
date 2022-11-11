#include "stack.h"

void spush(struct stack *s, int i) {
  s->values[++s->cur] = i;
  return;
}

int spop(struct stack *s) {
  return s->values[s->cur--];
}