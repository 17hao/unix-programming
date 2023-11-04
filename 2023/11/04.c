#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
  void (*addToTail)(struct ListNode *self, struct ListNode *node);
  char *(*toString)(struct ListNode *self);
};

void addToTail(struct ListNode *head, struct ListNode *node) {
  struct ListNode *cur = head;
  for (;;) {
    if (cur->next == NULL) {
      break;
    }
    cur = cur->next;
  }
  cur->next = node;
}

char *toString(struct ListNode *head) {
  struct ListNode *cur = head;
  char *str = malloc(1024);
  for (;;) {
    if (cur == NULL) {
      break;
    }
    sprintf(str, "%s%d ", str, cur->val);
    cur = cur->next;
  }
  return str;
}

int sum(int a, int b) {
  return a + b;
}

int main() {
  struct ListNode head = {.val = 0, .addToTail = addToTail, .toString = toString};
  struct ListNode node1 = {.val = 1};
  struct ListNode node2 = {.val = 2};
  struct ListNode node3 = {.val = 3};
  head.addToTail(&head, &node1);
  head.addToTail(&head, &node2);
  head.addToTail(&head, &node3);
  printf("%s\n", head.toString(&head));

  printf("========########========\n");

  int (*fn)(int, int) = sum;
  int res = fn(1, 2);
  printf("%d\n", res);
}