#include <stdio.h>
#include <stdlib.h>

extern char *buf;

void readFromBuf() {
    printf("extern buf = %s\n", buf);
}

extern char **environ; // defined in glibc posix/environ.c

// getenv is the only one specified by the C standard
// the function putenv and the extern environ are POSIX-specific
int main(int argc, char **argv) {
    putenv("k1=v1");
    for (char **tmp = environ; *tmp != NULL; tmp++) {
        printf("%s\n", *tmp);
    }

    printf("==== getenv ====\n");
    char *home = getenv("HOME");
    printf("HOME = %s\n", home);

    writeToBuf();
    readFromBuf();
}
