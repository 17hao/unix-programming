#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  //   char *strings[] = {"hello", ", ", "world", "!\n", NULL};
  char **strings = (char *[]){"hello", ", ", "world", "!\n", NULL};

  for (char **p = strings; *p != NULL; p++) {
    printf("%s", *p);
  }

  // error
  // char *chars[2] = {{'h', 'i', ' ', '\0'}, {'B', 'o', 'b', '\n', '\0'}};

  // chars is an array of two char pointers
  char *chars[2] = {(char[]){'h', 'i', ' ', '\0'},
                    (char[]){'B', 'o', 'b', '\n', '\0'}};

  for (int i = 0; i < 2; i++) {
    for (char *p = chars[i]; *p != '\0'; p++) {
      printf("%c", *p);
    }
  }

  // pchar is an array pointer. It points to an array of 2 elements.
  char arr[3][2] = {{'h', 'i', 'i'}, {'o', 'k', 'k'}};
  char(*pchar)[2] = NULL;
  pchar = arr;

  exit(EXIT_SUCCESS);
}