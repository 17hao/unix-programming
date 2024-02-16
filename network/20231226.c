#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define DEFAULT_PORT 8080
#define MAX_EVENTS 10
#define BUF_SIZE 5

char *trim(char *buf, int len) {
    printf("read from client, readCount=%d buf=%s, buf=", len, buf);
    for (int i = 0; i < len; i++) {
        printf("%d,", buf[i]);
    }
    printf("\n");

    if (buf[len - 2] == '\r' && buf[len - 1] == '\n') { // 边界case，输入zoo，buf=zoo\r\n，\r和\n会被截断
        printf("skip cr nl\n");
        char *res = malloc(sizeof(char) * (len - 2));
        for (int i = 0; i < len - 2; i++) {
            res[i] = buf[i];
        }
        return res;
    }

    char *copyOfBuf = malloc(sizeof(char) * len);
    strcpy(copyOfBuf, buf);
    return copyOfBuf;
}

void readFromSocket(int fd) {
    char content[1024];
    memset(content, 0, 1024);
    int ptr = 0;
    for (;;) {
        char buf[BUF_SIZE];
        int readCount = read(fd, buf, BUF_SIZE - 1); // read return 0 when client close connection
        if (readCount == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buf[readCount] = 0; // 如果不设置结束符，使用string相关函数（print %s，strlen）会造成UB
        char *trimmedBuf = trim(buf, readCount);
        for (int i = 0; i < strlen(trimmedBuf); i++) {
            content[ptr++] = trimmedBuf[i];
        }
        // printf("trimmedBuf=%s, strlen=%ld, content=%s, ptr=%d\n", trimmedBuf, strlen(trimmedBuf), content, ptr);
        if (strlen(trimmedBuf) < BUF_SIZE - 1) {
            printf("stop reading\n");
            break;
        }
    }
    content[ptr] = 0;
    printf("content=%s\n", content);
    if (strcmp(content, "close") == 0) {
        printf("close client connection\n");
        close(fd);
    } else {
        content[ptr++] = '\r';
        content[ptr++] = '\n';
        write(fd, content, ptr);
    }
}

int main() {
    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in srvAddr;
    memset(&srvAddr, 0, sizeof(struct sockaddr_in));
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = INADDR_ANY;
    srvAddr.sin_port = htons(DEFAULT_PORT);

    if (bind(listenSock, (struct sockaddr *)&srvAddr, sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(listenSock, 0) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("listening on %d\n", DEFAULT_PORT);

    int epfd = epoll_create(1);
    if (epfd < 0) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }
    struct epoll_event epollEv = {};
    epollEv.events = EPOLLIN;
    epollEv.data.fd = listenSock;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenSock, &epollEv) < 0) {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        struct epoll_event events[MAX_EVENTS];
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == listenSock) {
                struct sockaddr_in cliAddr;
                socklen_t cliAddrLen = sizeof(struct sockaddr_in);
                int connSock = accept(listenSock, (struct sockaddr *)&cliAddr, &cliAddrLen);
                if (connSock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                struct epoll_event connEv = {};
                connEv.events = EPOLLIN | EPOLLOUT;
                connEv.data.fd = connSock;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, connSock, &connEv) < 0) {
                    perror("epoll_ctl");
                    exit(EXIT_FAILURE);
                }
                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &cliAddr.sin_addr.s_addr, ip, INET_ADDRSTRLEN);
                printf("receive new connection, addr=%s, port=%d\n", ip, cliAddr.sin_port);
            } else if (events[i].events & EPOLLIN) {
                readFromSocket(events[i].data.fd);
            }

            if (events[i].events & (EPOLLRDHUP | EPOLLHUP)) {
                printf("connection closed\n");
                epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                close(events[i].data.fd);
            }
        }
    }
}