#include <stdio.h>
#include <stdbool.h>
/* Copy stdin to stdout, replacing consecutive spaces with a single space
   Edge case: a leading space is retained if there are leading spaces.
   Edge case: an empty file just doesn't echo anything, but emits a warning on stderr */
int main(void) {
  int c = getchar();
  if (c == EOF) {
    fprintf(stderr, "warning: no input\n");
    goto exit;
  }
  putchar(c);
  bool bl = (c == ' ');
  while ((c = getchar()) != EOF) {
    if ((!bl) || (c != ' ')) {
        putchar(c);
    }
    bl = (c == ' ');
  }
exit:
  return 0;
}