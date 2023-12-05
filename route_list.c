#include <arpa/inet.h>
#include <asm/types.h>
#include <errno.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

// === send netlink request ===

int openNetlink() {
  int sock = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);

  struct sockaddr_nl sa;
  memset(&sa, 0, sizeof(struct sockaddr_nl));
  sa.nl_family = AF_NETLINK;
  sa.nl_pid = getpid();

  if (bind(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr_nl)) < 0) {
    perror("bind");
    close(sock);
    return -1;
  }

  return sock;
}

int doRouteDumpReqeust(int sock) {
  struct {
    struct nlmsghdr hdr;
    struct rtmsg msg;
  } nlReq;

  nlReq.hdr.nlmsg_type = RTM_GETROUTE;                // man 7 rtnetlink
  nlReq.hdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP; // man 7 netlink;
  nlReq.hdr.nlmsg_len = sizeof(nlReq);
  nlReq.hdr.nlmsg_seq = time(NULL);
  nlReq.msg.rtm_family = AF_INET;

  return send(sock, &nlReq, sizeof(nlReq), 0);
}

// === read and parse netlink response ===

void rtnlPrintRoute(struct nlmsghdr *nlmsg) {
  struct rtmsg *routeEntry = NLMSG_DATA(nlmsg);
  struct rtattr *routeAttr = RTM_RTA(routeEntry);
  int len = RTM_PAYLOAD(nlmsg);

  if (routeEntry->rtm_table != RT_TABLE_MAIN) {
    return;
  }
  
  char src[32];
  char dst[32];
  char gateway[32];
  for (; RTA_OK(routeAttr, len); routeAttr = RTA_NEXT(routeAttr, len)) {
    printf("route attribute type=%d\n", routeAttr->rta_type);

    switch (routeAttr->rta_type) {
    case RTA_DST:
      inet_ntop(AF_INET, RTA_DATA(routeAttr), dst, sizeof(dst));
      break;
    case RTA_GATEWAY:
      inet_ntop(AF_INET, RTA_DATA(routeAttr), gateway, sizeof(gateway));
      break;
    case RTA_SRC:
      inet_ntop(AF_INET, RTA_DATA(routeAttr), src, sizeof(src));
      break;
    default:
      continue;
    }
  }
  printf("src=%s\tdst=%s\tgateway=%s\n", src, dst, gateway);
}

int getRouteDumpResponse(int sock) {
  struct sockaddr_nl sa;
  char buf[8192]; // TODO define cons
  struct iovec iov = {
      .iov_base = buf,
      .iov_len = 8192,
  };
  struct msghdr msg = {
      .msg_name = &sa,
      .msg_namelen = sizeof(struct sockaddr_nl),
      .msg_iov = &iov,
      .msg_iovlen = 1,
  };

  int len = recvmsg(sock, &msg, 0);
  if (len < 0) {
    return -1;
  }

  struct nlmsghdr *nlmsg = (struct nlmsghdr *)buf; // Undefined Behavior
  while (NLMSG_OK(nlmsg, len)) {
    if (nlmsg->nlmsg_type == RTM_NEWROUTE) {
      rtnlPrintRoute(nlmsg);
    }
    nlmsg = NLMSG_NEXT(nlmsg, len);
  }
  return 0;
}

int main() {
  int sock = openNetlink();

  if (doRouteDumpReqeust(sock) < 0) {
    perror("doRouteDumpRequest");
    close(sock);
    exit(EXIT_FAILURE);
  }

  getRouteDumpResponse(sock);
}
