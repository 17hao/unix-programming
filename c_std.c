#include <stdio.h>

// determine the C standard version used by compiler
int main() {
    printf("%d\n", __STDC__);
    printf("%ld\n", __STDC_VERSION__);
}
