// secion 5.4

#define BUF_SIZE 1024

static char allocbuf[BUF_SIZE]; // storage for alloc
static char *allocp;            // next free position

// return pointer to n characters
char *alloc(int n) {
    if (allocbuf + BUF_SIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

// free storage pointed to by p
void afree(char *p) {
    if (p >= allocbuf && p <= allocbuf + BUF_SIZE) {
        allocp = p;
    }
}