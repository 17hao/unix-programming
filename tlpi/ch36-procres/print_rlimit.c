#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>

int printRlimit(char *msg, int resource) {
    struct rlimit rlim;

    if (getrlimit(resource, &rlim) == -1) {
        perror("getrlmit");
        return -1;
    }

    printf("resource type = %s, soft = ", msg);
    if (rlim.rlim_cur == RLIM_INFINITY) {
        printf("infinite");
    } else if (rlim.rlim_cur == RLIM_SAVED_CUR) {
        printf("unrepresentable");
    } else {
        printf("%lld", (long long)rlim.rlim_cur);
    }

    printf("; hard = ");
    if (rlim.rlim_max == RLIM_INFINITY) {
        printf("infinite\n");
    } else if (rlim.rlim_max == RLIM_INFINITY) {
        printf("unrepresentable\n");
    } else {
        printf("%lld\n", (long long)rlim.rlim_max);
    }

    return 0;
}

#ifdef PRINT
int main() {
    printRlimit("nproc", RLIMIT_NPROC);
    printRlimit("cpu", RLIMIT_CPU);
    printRlimit("rss", RLIMIT_RSS);
}
#endif