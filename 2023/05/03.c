// echo server, listen on tcp port 9000

#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9000
#define LISTEN_BACKLOG 50
#define BUF_SIZE 1024

int main(void) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return EXIT_FAILURE;
    }

    if (listen(sfd, LISTEN_BACKLOG) < 0) {
        perror("listen");
        return EXIT_FAILURE;
    }

    for (;;) {
        socklen_t len = sizeof(addr);
        int afd = accept(sfd, (struct sockaddr *)&addr, &len);
        if (afd < 0) {
            perror("accept");
            return EXIT_FAILURE;
        }

        char buf[BUF_SIZE];
        if (recv(afd, buf, BUF_SIZE, 0) < 0) {
            perror("recv");
            return EXIT_FAILURE;
        }
        printf("%s", buf);
    }

    return EXIT_SUCCESS;
}