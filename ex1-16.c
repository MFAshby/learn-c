#include <stdio.h> 
#define MAXLINE 4 /* maximum input line size */  
int getln(char line[], int maxline); 
void copy(char to[], char from[]);
int min(int,int);
/* print longest input line */ 
int main() {  
  int len; /* current line length */  
  int max; /* maximum length seen so far */  
  char line[MAXLINE]; /* current input line */  
  char longest[MAXLINE]; /* longest line saved here */  
  max = 0;  
  while ((len = getln(line, MAXLINE)) > 0)  
    if (len > max) {  
      max = len;  
      copy(longest, line);  
    } 
  if (max > 0) /* there was a line */  
    printf("%s", longest);  
  return 0; 
}

/* getln: read up to lim characters from a line into s, 
   return length of the line */ 
int getln(char s[], int lim) {  
  int c = getchar();
  int i = 0;
  while (c != EOF && c != '\n') {
    if (i< lim-1)
      s[i] = c;
    i++;
    c = getchar();
  }
  s[min(i, lim-1)] = '\0';  
  return i; 
}  

/* copy: copy ′from′ into ′to′; 
   assume to is big enough */ 
void copy(char to[], char from[]) {  
  int i;  
  i = 0; 
  while ((to[i] = from[i]) != '\0')  
    ++i; 
}

int min(int a, int b) {
  return a< b?a:b;
}