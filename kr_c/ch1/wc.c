// section 1.5.4

#include <stdio.h>

#define IN 1  // inside a word
#define OUT 0 // outside a word

// count the lines, words, characters in input
int main(int argc, char **argv) {
    int c;
    int nl = 0, nw = 0, nc = 0;
    int state = OUT;

    while ((c = getchar()) != EOF) {
        nc++;

        if (c == '\n') {
            nl++;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            nw++;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}