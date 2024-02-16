struct Queue {
    struct ListNode *head;
    struct ListNode *tail;
};

// queue push
void qpush(struct Queue *, int);

// queue pop
int qpop(struct Queue *);