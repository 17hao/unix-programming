#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define INT_SIZE sizeof(int)

void print(int *in);
void sieve(int *in);

// https://pdos.csail.mit.edu/6.S081/2022/labs/util.html
// https://swtch.com/~rsc/thread/
// TLPI ch 44
int main(int argc, char *argvp[]) {
  int fds[2];

  pipe(fds);

  if (fork() == 0) {
    // sieve(fds);
    print(fds);
  } else {
    for (int i = 2; i <= 5; i++) {
      write(fds[1], &i, INT_SIZE);
      sleep(1);
    }
    close(fds[1]);
    wait(0);
    exit(0);
  }
}

void print(int *in) {
  // close(in[1]);
  int num;

  // read(in[0], &num, INT_SIZE);
  // fprintf(stdout, "%d\n", num);

  int k;
  while ((k = read(in[0], &num, INT_SIZE)) > 0) {
    fprintf(stdout, "%d\n", num);
  }
}

void sieve(int *in) {
  close(in[1]);

  int num, p;
  if (read(in[0], &p, INT_SIZE) == 0) {
    close(in[0]);
    exit(0);
  }

  fprintf(stdout, "pid=%d, ppid=%d, prime %d\n", getpid(), getppid(), p);

  int out[2];
  pipe(out);
  if (fork() == 0) {
    sieve(out);
  } else {
    while (read(in[0], &num, INT_SIZE) > 0) {
      fprintf(stdout, "pid=%d, ppid=%d, num %d\n", getpid(), getppid(), num);
      if (num % p != 0) {
        write(out[1], &num, INT_SIZE);
      }
    }
    close(out[0]);
    close(out[1]);
    wait(0);
  }
  exit(0);
}