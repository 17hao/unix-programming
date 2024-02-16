#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Usage: ./t_execve ./envargs
// execve: v means argv, e means environ
// execve 通常和 fork 一起使用
int main(int argc, char *argv[]) {
    char *envVec[10];
    envVec[0] = "k1=v1";
    envVec[1] = "k2=v2";
    envVec[2] = NULL;

    char *argVec[10];
    argVec[0] = strchr(argv[1], '/');
    if (argVec[0] != NULL) {
        argVec[0]++;
    }
    argVec[1] = "arg1";
    argVec[2] = "arg2";
    argVec[3] = NULL;

    execve(argv[1], argVec, envVec);
    exit(EXIT_SUCCESS);
}