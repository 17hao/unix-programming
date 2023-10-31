#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void v1() {
  printf("hello, world\n");
  write(STDOUT_FILENO, "abc\n", 4);

  if (fork() == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

void v2() {
  printf("hello, world\n");
  write(STDOUT_FILENO, "abc\n", 4);

  pid_t pid = fork();

  switch (pid) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    _exit(EXIT_SUCCESS);
    break;
  default:
    exit(EXIT_SUCCESS);
  }
}

/*
Usage:
cc fork_stdio_buf.c
./a.out
./a.out > tmp && cat tmp


1. printf的输出保存在stdio buffer，属于用户态的一部分;write的输出写入到kernle buffer
2. exit会刷新stdio buffer到kernel buffer
3. fork创建的子进程会复制父进程用户态的stdio buffer
4. terminal buffer遇到换行符就输出，重定向到terminal时，printf输出换行符，先于write输出结果
5. terminal重定向到文件时，printf的输出仍在用户态stdio buffer,直到执行exit才被刷新到kernel buffer,所以晚于write输出
*/
int main() {
  v1();
  // v2();
}