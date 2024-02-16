#include <stdio.h>
#include <stdlib.h>

typedef char *string;

struct user {
    int id;
    string name;
};

void printUsers(struct user (*pusers)[3]) {
    printf("user={id=%d, name=%s}\n", (**pusers).id, (**pusers).name);
    printf("user={id=%d, name=%s}\n", (*(*pusers + 1)).id, (*(*pusers + 1)).name);
    printf("user={id=%d, name=%s}\n", (*(*pusers + 2)).id, (*(*pusers + 2)).name);

    printf("================\n");

    struct user *users = *pusers;
    // struct user users[3] = *pusers; // invalid
    for (int i = 0; i < 3; i++) {
        printf("user={id=%d, name=%s}\n", users[i].id, users[i].name);
    }
}

void print2DArray(int (*nums)[3]) {
    printf("nums[0][1]=%d\n", *(*nums + 1));
    printf("nums[1][2]=%d\n", *(*(nums + 1) + 2));
    printf("nums[1][0]=%d\n", **(nums + 1));
}

int main(void) {
    int nums[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    print2DArray(nums);

    struct user users[3];
    struct user u1 = {
        .id = 1,
        .name = "u1",
    };
    struct user u2 = {
        .id = 2,
        .name = "u2",
    };
    struct user u3 = {
        .id = 3,
        .name = "u3",
    };
    users[0] = u1;
    users[1] = u2;
    users[2] = u3;
    printUsers(&users);
}