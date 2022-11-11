#define STACK_SIZE 1 << 10

struct stack {
  int values[STACK_SIZE];
  int cur;
};

// stack push
void spush(struct stack *, int);

// stack pop
int spop(struct stack *);