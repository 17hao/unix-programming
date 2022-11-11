#include "queue.h"

#include "list.h"

void qpush(struct Queue *q, int i) {
  struct ListNode n1 = {.val = i};
  if (!q->head && !q->tail) {
    struct ListNode n2 = {.val = i};
    q->head = &n1;
    q->tail = &n2;
    return;
  }
  q->tail->next = &n1;
  n1.pre = q->tail;
  q->tail = q->tail->next;
  return;
}

int qpop(struct Queue *q) {
  int i = q->head->val;
  q->head = q->head->next;
  if (!q->head) {
    q->tail = 0;
  }
  return i;
}