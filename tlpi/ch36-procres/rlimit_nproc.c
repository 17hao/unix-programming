#include "print_rlimit.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: %s soft-limit hard-limit\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Initial maximum process limits: ");
    printRlimit("nproc", RLIMIT_NPROC);

    // set new process limits
    struct rlimit rl;
    rl.rlim_cur = atoi(argv[1]);
    rl.rlim_max = atoi(argv[2]);
    if (setrlimit(RLIMIT_NPROC, &rl) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    printf("New maximum process limits: ");
    printRlimit("nproc", RLIMIT_NPROC);

    // create as many children as possible
    for (int i = 1;; i++) {
        pid_t childPid;
        switch (childPid = fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            exit(EXIT_SUCCESS);
        default:
            printf("child %d pid=%ld started\n", i, (long)getpid());
        }
    }
}