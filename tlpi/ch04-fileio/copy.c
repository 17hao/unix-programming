#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef BUFSIZE
#define BUFSIZE 1024
#endif

// ./copy copy.c /dev/tty copy a regular file to this terminal.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s old-file new-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 1. open source file
    int inputFd = open(argv[1], O_RDONLY);

    // 2. create and open destination file
    int openFlags = O_WRONLY | O_CREAT;
    int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 644
    int outputFd = open(argv[2], openFlags, filePerms);

    // 3. transfer data until we encounter the end of the source file
    char buf[BUFSIZE];
    int numRead;
    while ((numRead = read(inputFd, buf, BUFSIZ)) > 0) {
        write(outputFd, buf, numRead);
    }

    // 4. close files
    close(inputFd);
    close(outputFd);
    exit(EXIT_SUCCESS);
}