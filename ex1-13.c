#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define max_word 100
#define max(a, b) ((a) > (b) ? (a) : (b))

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
  uint32_t lens[max_word+1]={0};
  state s = out;
  uint32_t cl = 0;
  while(true) {
    int c = fgetc(input);
    if (is_word(c)){
      if (s == out) {
        s = in;
        cl=1;
      } else { 
        cl++;
      }
    } else {
      if (s == in) {
        s = out;
        if (cl > max_word) {
          printf("cl=%d\n", cl);
          fprintf(output_err, "word too long\n");
          fflush(output_err);
          return 1;
        }
        lens[cl]++;
      } else {
        // do nothing I guess
      } 
    }

    if (c == EOF) {
      break;
    }
  }
  // Do 2 passes to find the longest word length with some data in it
  uint16_t mx = 0;
  for(uint16_t i=1;
      i<=max_word;
      i ++)
    mx = max(mx, lens[i]>0 ? i : 0);
  for(uint16_t i=1;
      i<=mx;
      i ++) {
    fprintf(output, "%2d: ",i);
    for(uint16_t j=0;
        j<lens[i];
        j++)
      fputc('-', output);
    fputc('\n', output);
  }
  fflush(output);
  return 0;
}

#ifndef test

int main(void) {
    return whisto(stdin, stdout, stderr);
}

#else

#include "CuTest.h"

void do_test(CuTest* tc, char* input, const char* expected, const char* err_expected, int res_expected) {
    char buf[100] = {0};
    char err_buf[100] = {0};
    FILE* tin = fmemopen(input, strlen(input), "r");
    FILE* tout = fmemopen(buf, 100, "w");
    FILE* terr = fmemopen(err_buf, 100, "w");
    int res = whisto(tin, tout, terr);
    CuAssertIntEquals(tc, res_expected, res);
    CuAssertStrEquals(tc, expected, buf);
    CuAssertStrEquals(tc, err_expected, err_buf);
}
void test_whisto_empty(CuTest* tc) {
    do_test(tc, "", "", "", 0);
}
void test_whisto_oneword(CuTest* tc) {
    do_test(tc, "fo", 
      " 1: \n"
      " 2: -\n", 
      "", 
      0);
}
void test_whisto_leadtrailspace(CuTest* tc) {
    do_test(tc, "  fuzz fizz   bar  ", 
      " 1: \n"
      " 2: \n"
      " 3: -\n"
      " 4: --\n", 
      "",
      0);
}
void test_whisto_overflow(CuTest* tc) {
    // 101 characters
    do_test(tc, "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901",
      "",
      "word too long\n",
      1);
}
CuSuite* whisto_suite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_whisto_empty);
    SUITE_ADD_TEST(suite, test_whisto_oneword);
    SUITE_ADD_TEST(suite, test_whisto_leadtrailspace);
    SUITE_ADD_TEST(suite, test_whisto_overflow);
    return suite;
}
int main(void) {
    CuString* output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    CuSuiteAddSuite(suite, whisto_suite());
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    return 0;
}

#endif
  