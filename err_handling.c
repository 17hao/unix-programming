#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // error handling from system calls
  int fd = open("foo", O_RDONLY);
  if (fd == -1) {
    if (errno == ENOENT) {
      perror("open");  // fcntl.h open: No such file or directory
    } else {
      strerror(errno);  // string.h
    }
    exit(EXIT_FAILURE);
  }
}