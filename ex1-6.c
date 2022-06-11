#include <stdio.h>
int main(void) {
  while (1) {
    printf("%d\n", getchar()==EOF);
  }
  return 0;
}