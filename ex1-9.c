#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Copy stdin to stdout, replacing consecutive spaces with a single space
   Edge case: a leading space is retained if there are leading spaces.
   Edge case: an empty file just doesn't echo anything, but emits a warning on stderr */
int remspace(FILE* fin, FILE* fout, FILE* ferr) {
  int c = fgetc(fin);
  if (c == EOF) {
    fprintf(ferr, "warning: no input\n");
    goto exit;
  }
  fputc(c, fout);
  bool bl = (c == ' ');
  while ((c = fgetc(fin)) != EOF) {
    if ((!bl) || (c != ' ')) {
        fputc(c, fout);
    }
    bl = (c == ' ');
  }
exit:
  fflush(fout);
  fflush(ferr);
  return 0;
}

#ifndef test

int main(void) {
    return remspace(stdin, stdout, stderr);
}

#else

#include "CuTest.h"

void do_test(CuTest* tc, char* input, const char* expected, const char* err_expected) {
    char buf[100] = {0};
    char err_buf[100] = {0};
    FILE* tin = fmemopen(input, strlen(input), "r");
    FILE* tout = fmemopen(buf, 100, "w");
    FILE* terr = fmemopen(err_buf, 100, "w");
    int res = remspace(tin, tout, terr);
    CuAssertIntEquals(tc, 0, res);
    CuAssertStrEquals(tc, expected, buf);
    CuAssertStrEquals(tc, err_expected, err_buf);
}
void test_remspace_empty(CuTest* tc) {
    do_test(tc, "", "", "warning: no input\n");
}
void test_remspace_oneword(CuTest* tc) {
    do_test(tc, "foobar", "foobar", "");
}
void test_remspace_leadtrailspace(CuTest* tc) {
    do_test(tc, "  foo   bar  ", " foo bar ", "");
}
CuSuite* remspace_suite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_remspace_empty);
    SUITE_ADD_TEST(suite, test_remspace_oneword);
    SUITE_ADD_TEST(suite, test_remspace_leadtrailspace);
    return suite;
}
int main(void) {
    CuString* output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    CuSuiteAddSuite(suite, remspace_suite());
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    return 0;
}

#endif
