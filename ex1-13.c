#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define max_word 100

typedef enum _state {in,out} state;
bool is_word(char c) {
  return c != ' ' 
   && c != '\t' 
   && c != '\n';
}
/* print a histogram of word lengths
   read from input
   print histo to output
   print errors warnings to output_err */
int whisto(FILE* input, FILE* output, FILE* output_err) {
  uint32_t lens[max_word]={0};
  int c = fgetc(input);
  if (c == EOF) {
    fprintf(output_err, "warning: no input!\n");
    goto spout;
  }
  state s = is_word(c) ? in : out;
  uint32_t cl = s == in ? 1 : 0;
  while ((c = fgetc(stdin))!= EOF){
    if (is_word(c)){
      if (s == in) {
        cl++;
      } else { 
        s = in;
        cl=1;
      }
    } else {
      if (s == in) {
        s = out;
        lens[cl]++;
      } else {
        // do nothing I guess
      }
    }
  }
  // need to count final word 
  if (s == in) {
    lens[cl]++;
  }
spout:
  for(uint16_t i=1;
      i<max_word;
      i ++) {
    fprintf(output, "%2d: ",i);
    for(uint16_t j=0;
        j<lens[i];
        j++)
      fputc('-', output);
    fputc('\n', output);
  }
  return 0;
}

int main(void){
  whisto(stdin, stdout, stderr);
}
  