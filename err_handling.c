#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // error handling from system calls
    int fd = open("foo", O_RDONLY);
    if (fd == -1) {
        if (errno == ENOENT) {
            printf("=== perror ===\n");
            perror("open"); // fcntl.h open: No such file or directory
        }
        printf("=== stderror ===\n");
        char *err = strerror(errno); // string.h
        fprintf(stderr, "%s\n", err);
        exit(EXIT_FAILURE);
    }
}