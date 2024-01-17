#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s string\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid_t pid = fork();
  switch (pid) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0: // child reads from pipe
    close(pipefd[1]);
    pid_t pid = getpid();
    char str[20];
    sprintf(str, "pid=%d\n", pid);
    write(STDOUT_FILENO, &str, strlen(str));
    char buf;
    while (read(pipefd[0], &buf, 1)) {
      write(STDOUT_FILENO, &buf, 1);
    }
    close(pipefd[0]);
    break;
  default: // parent writes to pipe
    close(pipefd[0]);
    write(pipefd[1], argv[1], strlen(argv[1]));
    close(pipefd[1]);
    wait(NULL); // wait for child
    exit(EXIT_SUCCESS);
  }
}