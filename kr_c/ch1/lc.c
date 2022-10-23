// section 1.5.3

#include <stdio.h>

// count lines in input
int main(int argc, char **argv) {
  int c;
  int nl = 0; // number of lines
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      nl++;
    }
  }
  printf("number of lines is %d\n", nl);
}