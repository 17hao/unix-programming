#include <stdio.h>
#include <string.h>

struct user {
    int id;
    char *name;
};

// <0 if e1<e2, =0 if e1=e2, >0 if e1>e2
int compareById(struct user *u1, struct user *u2) {
    return u1->id - u2->id;
}

int compareByName(struct user *u1, struct user *u2) {
    return strcmp(u1->name, u2->name);
}

void swap(struct user **users, int i, int j) {
    struct user *tmp = users[i];
    users[i] = users[j];
    users[j] = tmp;
}

// https://en.wikipedia.org/wiki/Insertion_sort
void insertionSort(struct user **users, int size, int (*comp)(void *, void *)) {
    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0; j--) {
            if (comp(users[j], users[j - 1]) < 0) {
                swap(users, j, j - 1);
            }
        }
    }
}

void printUser(struct user *e) {
    printf("{\n");
    printf("\tid=%d,\n", e->id);
    printf("\tname=%s,\n", e->name);
    printf("}\n");
}

int main(int argc, char **argv) {
    int i = 1, j = 5;
    if (i - j) {
        printf("i-j\n");
    } else {
        printf("j-i\n");
    }

    if ((i - j) < 0) {
        printf("i - j < 0\n");
    } else {
        printf("j - i < 0\n");
    }

    struct user e1 = {.id = 5, .name = "Bob"};
    struct user e2 = {.id = 3, .name = "Alice"};
    struct user e3 = {.id = 1, .name = "Mike"};
    struct user *users[] = {&e1, &e2, &e3};
    // insertionSort(users, 3, (int (*)(void *, void *))compareById);
    insertionSort(users, 3, (int (*)(void *, void *))compareByName);
    for (int i = 0; i < 3; i++) {
        printUser(users[i]);
    }
}