#include <stdio.h>
#include <string.h>

int main(void) {
  int x = 20, y = 4;
  char str[x / y];
  printf("after memset: str=%s\n", str);

  memset(str, 0, sizeof(str));
  printf("before memset: str=%s\n", str);

  // char str2[x / y] = {0}; compile error!
  // char str2[5] = {0};
  char str2[5];
  printf("str2=%s\n", str2);

  int arr2D[3][4];
  int arr[4] = {1};
  memcpy(arr2D[0], arr, sizeof(arr));
  printf("arr2D[0]: ");
  for (int i = 0; i < 4; i++) {
    printf("%d ", arr2D[0][i]);
  }
  printf("\n");
  int arr2[4];
  memcpy(arr2, arr2D[0], sizeof(arr2));
  printf("arr2: ");
  for (int i = 0; i < 4; i++) {
    printf("%d ", arr2[i]);
  }
}
