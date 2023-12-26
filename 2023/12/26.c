#include <stdio.h>
#include <string.h>

int main() {
  char buf[10] = "close\r\n"; // buf != "close"
  if (strcmp(buf, "close") == 0) {
    printf("equal\n");
  } else {
    printf("not equal\n");
  }
}