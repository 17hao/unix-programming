#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void mountTmpFS(char *path) {
  if (mkdir(path, 0777) != 0) {
    if (errno != EEXIST) {
      perror("mkdir");
      // printf("mkdir failed, err=%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  char *wd = getcwd(malloc(PATH_MAX), PATH_MAX);
  // printf("wd=%s\n", wd);
  if (mount(wd, path, NULL, MS_BIND, NULL) != 0) {
    printf("mount failed, err=%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  if (chroot(path) != 0) {
    printf("chroot failed, err=%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  DIR *dir = opendir("/");
  for (;;) {
    struct dirent *e = readdir(dir);
    if (e == NULL) {
      break;
    }
    if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) {
      continue;
    }
    // printf("|-- %s\n", e->d_name);
    printf("├── %s\n", e->d_name);
  }
  // if (umount(tmpfs) != 0) {
  // printf("umount failed, err=%s\n", strerror(errno));
  // exit(EXIT_FAILURE);
  // }
}

void umountTmpFS(char *path) {
  if (umount(path) != 0) {
    printf("umount failed, err=%s, path=%s\n", strerror(errno), path);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv) {
  char *tmpfs = "/tmp/my-tmpfs";
  int subCmd = 0;
  // sudo ./a.out <mount|umount>
  if (argc == 2) {
    if (strcmp(argv[1], "mount") == 0) {
      subCmd = 1;
    } else if (strcmp(argv[1], "umount") == 0) {
      subCmd = 2;
    }
  }
  switch (subCmd) {
  case 1:
    mountTmpFS(tmpfs);
    break;
  case 2:
    umountTmpFS(tmpfs);
    break;
  default:
    printf("subCmd=%d, exit\n", subCmd);
    break;
  }
}