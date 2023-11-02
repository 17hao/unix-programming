#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CMD_SIZE 200

int main(int argc, char **argv) {
  setbuf(stdout, NULL);
  printf("parent pid=%d\n", (long)getpid());

  switch (fork()) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    printf("child pid=%d\n", getpid());
    _exit(EXIT_SUCCESS);
  default:
    sleep(3);
    char cmd[CMD_SIZE];
    snprintf(cmd, CMD_SIZE, "ps -e -o user,pid,ppid,tty,stat,start,time,cmd | grep %s", basename(argv[0]));
    system(cmd);
  }
}