#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

struct threadArgs {
    char *arg1;
    int arg2;
};

void *threadStart(void *arg) {
    printf("pthread_self returns %ld\n", pthread_self());
    printf("gettid returns %ld\n", syscall(SYS_gettid));

    struct threadArgs *threadArgs = arg;
    char *uarg1 = strdup(threadArgs->arg1);
    if (uarg1 == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    for (char *p = uarg1; *p != '\0'; p++) {
        *p = toupper((unsigned char)*p);
    }
    return uarg1;
}

int main() {
    pthread_t thread_id = 1;
    struct threadArgs threadArgs = {.arg1 = "arg", .arg2 = 1};
    if (pthread_create(&thread_id, NULL, &threadStart, &threadArgs) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    void *res;
    if (pthread_join(thread_id, &res) != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
    printf("res=%s\n", (char *)res);
    exit(EXIT_SUCCESS);
}