#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Seek to the head of file.
void seekToHead(FILE *f) {
    if (fseek(f, 0, SEEK_SET) != 0) {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    long position = ftell(f);
    printf("position=%ld\n", position);
}

// Show max tcp backlog and syn backlog.
// https://stackoverflow.com/questions/45807792/whats-tcp-backlog-in-redis-conf
// https://stackoverflow.com/questions/36594400/what-is-backlog-in-tcp-connections
int main() {
    FILE *f1 = fopen("/proc/sys/net/core/somaxconn", "r");
    FILE *f2 = fopen("/proc/sys/net/ipv4/tcp_max_syn_backlog", "r");
    if (!f1 || !f2) {
        strerror(errno);
        exit(EXIT_FAILURE);
    }

    // fsanf
    int max_tcp_backlog;
    fscanf(f1, "%d", &max_tcp_backlog);
    printf("max_tcp_backlog=%d\n", max_tcp_backlog);
    int syn_backlog;
    fscanf(f2, "%d", &syn_backlog);
    printf("syn_backlog=%d\n", syn_backlog);

    seekToHead(f1);

    // fgets
    char str[5];
    while (fgets(str, 5, f1) != NULL) {
        printf("%s", str);
    }

    seekToHead(f1);

    // fgetc
    char c;
    while ((c = fgetc(f1)) != EOF) {
        printf("%c", c);
    }

    fclose(f1);
    fclose(f2);
}