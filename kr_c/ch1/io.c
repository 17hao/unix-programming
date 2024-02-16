// section 1.5.1

#include <stdio.h>

int main(int argc, char **argv) {
    // char c; We can't use char since c must be big enough to hold EOF.
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}