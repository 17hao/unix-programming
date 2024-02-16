// Simple version of cp(1)
// p1044 exercise 49-1

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: cp [src] [dst]\n");
        exit(EXIT_FAILURE);
    }

    int src = open(argv[1], O_RDONLY);
    int dst;
    if (access(argv[2], F_OK) == 0) {
        // file exist
        dst = open(argv[2], O_RDWR);
    } else {
        dst = open(argv[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }

    struct stat st;
    if (fstat(src, &st) < 0) {
        char *err = strerror(errno);
        printf("fstat: %s\n", err);
        exit(EXIT_FAILURE);
    }

    if (ftruncate(dst, st.st_size) < 0) {
        char *err = strerror(errno);
        printf("ftruncate: %s\n", err);
        exit(EXIT_FAILURE);
    }

    char *srcAddr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, src, 0);
    char *dstAddr = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, dst, 0);
    if (srcAddr == MAP_FAILED || dstAddr == MAP_FAILED) {
        char *err = strerror(errno);
        printf("ftruncate: %s\n", err);
        exit(EXIT_FAILURE);
    }
    memcpy(dstAddr, srcAddr, st.st_size);

    // debug
    printf("=== src ===\n");
    write(STDOUT_FILENO, srcAddr, st.st_size);
    printf("=== dst ===\n");
    write(STDOUT_FILENO, dstAddr, st.st_size);

    exit(EXIT_SUCCESS);
}