#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct base {
    int id;
};

struct seller {
    struct base base;
    char *name;
};

struct customer {
    struct base base;
    char *location;
};

struct keyboard {
    char *brand;
    char *layout;
    char *owner;
    char *(*toString)(struct keyboard *);
};

char *toString(struct keyboard *k) {
    char *buf = malloc(1024);
    sprintf(buf, "brand=%s, layout=j%s, owner=%s\n", k->brand, k->layout, k->owner);
    return buf;
}

char *f1(struct keyboard *k) {
    return (char *)k;
}

void f2(struct keyboard *k, char *buf) {
    memcpy(buf, k, sizeof(struct keyboard));
}

// proper way
void f3(char *buf, struct keyboard *k) {
    memcpy(k, buf, sizeof(struct keyboard));
    k->owner = "f3";
}

// unexpected
void f4(char *buf, struct keyboard *k) {
    k = (struct keyboard *)buf;
    printf("[debug] f4kb=%s", k->toString(k));
    k->owner = "f4";
}

void f5(char *buf, struct keyboard **k) {
    *k = (struct keyboard *)buf;
    printf("[debug] f5kb=%s", (*k)->toString(*k));
    (*k)->owner = "f5";
}

int main() {
    // struct seller s = {.base = {.id = 1}, .name = "s1"};
    // f1((struct base *)&s);

    struct keyboard k = {.brand = "HHKB", .layout = "en_us", .owner = "main", .toString = toString};

    char *strK = f1(&k);
    printf("k=%s\n", strK);

    char *buf = malloc(sizeof(struct keyboard));
    f2(&k, buf);

    struct keyboard f3kb;
    f3(strK, &f3kb);
    printf("f3kb's owner=%s\n", f3kb.owner);

    struct keyboard f4kb;
    f4(buf, &f4kb);
    printf("f4kb's owner=%s\n", f4kb.owner);

    struct keyboard *f5kb;
    f5(buf, &f5kb);
    printf("f5kb's owner=%s\n", f5kb->owner);
}