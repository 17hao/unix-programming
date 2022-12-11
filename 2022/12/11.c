// 1. print hello, world
// 2. create a child process
// 3. count lines of 11.c
// 4. print parent's process id

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  printf("[pid=%d]  hello, world\n", getpid());

  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork faild.\n");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {  // child process
    printf("[pid=%d]  I am child process\n", getpid());
    printf("wc 11.c\n");
    char *args[2];
    args[0] = "wc";
    args[1] = "11.c";
    args[2] = NULL;
    int res = execvp("wc", args);
    if (res < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  } else {
    pid_t child = wait(NULL);
    if (child < 0) {
      fprintf(stderr, "wait failed.\n");
      exit(EXIT_FAILURE);
    }
    printf("[pid=%d]  child process=%d\n", getpid(), pid);
  }

  return EXIT_SUCCESS;
}