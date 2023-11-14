#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT_NUM "5000"
#define BACKLOG 50

// WIP
int main(int argc, char **argv) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_INET;
  hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

  struct addrinfo *res;
  if (getaddrinfo(NULL, PORT_NUM, &hints, &res) != 0) {
    perror("getaddrinfo");
    exit(EXIT_FAILURE);
  }

  struct addrinfo *rp;
  int sfd;
  for (rp = res; rp != NULL; rp = rp->ai_next) {
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1) {
      continue;
    }

    if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
      break;
    }

    close(sfd);
  }

  if (rp == NULL) {
    printf("Couldn't bind socket to address");
    exit(EXIT_FAILURE);
  }

  if (listen(sfd, BACKLOG) == -1) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  for (;;) {
    struct sockaddr caddr;
    socklen_t addrlen = sizeof(caddr);
    int cfd = accept(sfd, &caddr, &addrlen);
    if (cfd == -1) {
      perror("accept");
      continue;
    }

    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    if (getnameinfo(&caddr, addrlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
      printf("host=%s, serv=%s\n", hbuf, sbuf);
    }
  }
}