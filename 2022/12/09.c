#include <stdio.h>

int main(void) {
    unsigned int i = 0x00646c72;
    printf("H%x Wo%s\n", 57616, &i); // He110 World
}