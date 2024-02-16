// Display environment and argument list.

#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]=%s\n", i, argv[i]);
    }

    for (char **env = environ; *env != NULL; env++) {
        printf("environ: %s\n", *env);
    }
}