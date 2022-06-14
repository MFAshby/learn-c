#include <stdio.h>
#define minline 5
/* reads lines from stdin 
   outputs any lines over minlines
   characters long */
int main(void) {
  int c, l = 0;
  char buf[minline];
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      if (l>minline)
        putchar(c);
      l = 0; 
      for (int i=0;i<minline;i++)
        buf[i]=0;
    } else if (l<minline) {
      buf[l]=c;
      l++;
    } else {
      if (l==minline) 
        for (int i=0;i<minline;i++)
          putchar(buf[i]);
      putchar (c);
      l++;
    }
  }
  return 0;
}