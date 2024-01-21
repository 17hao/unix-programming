#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>

void handleReplyErr(redisReply *reply) {
  if (reply->type == REDIS_REPLY_ERROR) {
    printf("Error: %s\n", reply->str);
    exit(EXIT_FAILURE);
  }
}

// cc 21.c -lhiredis
int main(void) {
  redisContext *c = redisConnect("81.68.104.220", 16379);
  if (c == NULL || c->err) {
    if (c) {
      printf("Error: %s\n", c->errstr);
    } else {
      printf("Can't allocate redis context\n");
    }
    exit(EXIT_FAILURE);
  }
  redisReply *reply;
  reply = redisCommand(c, "auth 123456");
  handleReplyErr(reply);
  reply = redisCommand(c, "get k1");
  handleReplyErr(reply);
  printf("k1=%s\n", reply->str);
  redisFree(c);
}