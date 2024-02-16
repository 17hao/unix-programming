#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_SIZE 4

int main(int argc, char *argv[]) {
    char buf[512];
    strcpy(buf, "a");
    strcat(buf, "b");
    strcat(buf, "c");
    printf("buf=%s\n", buf);

    // 这个例子中，通过数组的偏移给指针p赋值。赋值后，指针指向数组，对p的操作将反应在数组上。
    // 数组指向数组的起始位置，通过下标获取数组中间的元素；指针则可以左右移动，*p++ 通过算数运算实现指针的移动。
    char *p;
    // p = buf + 1;
    p = buf + strlen(buf);
    *p++ = '/';
    char str[STR_SIZE] = "ij";
    printf("p=%s\n", p);
    printf("buf=%s\n", buf);
    memmove(p, str, STR_SIZE);
    p[12] = 0;
    printf("after memmove\n");
    printf("p=%s\n", p);
    printf("buf=%s\n", buf);

    DIR *dir = opendir("/root");
    if (dir == NULL) {
        fprintf(stderr, "opendir error\n");
        exit(EXIT_FAILURE);
    }
    struct dirent *de = readdir(dir);
    printf("d_name=%s\n", de->d_name);

    // Linux can't read from a directory!
    // int fd = open("/usr/local", O_RDONLY);
    // struct dirent *de;
    // read(fd, de, sizeof(de));
    // if (errno == EISDIR) {
    //   perror("open");
    //   exit(EXIT_FAILURE);
    // }
    // printf("d_name=%s\n", de->d_name);
}