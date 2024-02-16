#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // current wd
    char *buf = malloc(PATH_MAX);
    char *wd = getcwd(buf, PATH_MAX);
    printf("current work dir is %s\n", wd);

    // list files in wd
    DIR *currentDir = opendir(wd);
    if (errno != 0) {
        printf("errno=%d\n", errno);
        exit(EXIT_FAILURE);
    }
    printf("%s\n", wd);
    for (;;) {
        struct dirent *e = readdir(currentDir);
        if (e == NULL) {
            break;
        }
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) {
            continue;
        }
        printf("|-- %s\n", e->d_name);
    }
}