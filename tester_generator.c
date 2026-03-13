#include <stdio.h>

int main() {
  int i = 0;

  while (i < 100000) {
    printf("key %i\nvalue %i\n", i, i);
    i++;
  }
  printf("\n");
  i = 0;
  while (i < 100000) {
    printf("key %i\n", i);
    i++;
  }
}
