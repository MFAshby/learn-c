#include <stdio.h>

int main(void) {
  int c;
  uint32_t nl = 0, tb = 0, bl = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      bl++;
    } else if (c == '\n') {
      nl++;
    } else if (c == '\t') {
      tb++;
    }
  }
  printf("nl=%ld tb=%ld bl=%ld\n", nl, tb, bl);
  return 0;
}