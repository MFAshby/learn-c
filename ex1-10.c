#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Track whether we are inside or outside a word */
typedef enum _state {IN,OUT} state;

/* true if c is a 'word' character (not a blank, space, or a tab)  */
bool is_word(char c) {
    return c != ' ' && c != '\t' && c != '\n';
}

/* Counts characters, lines, and words from stdin. 

   'characters' are single byte characters. No handling for encodings in c standard lib.
   'lines' are newline characters.
   'words' are contiguous sequences of characters  other than space, tab, newline */
int main(void) {
    int c;
    state s = OUT;
    uint32_t cc = 0, lc = 0, wc = 0;
    while ((c = getchar()) !=  EOF) {
        cc++;
        if (c == '\n') {
            lc++;
        }
        if (!is_word(c)) {
            s = OUT;
        } else if (s == OUT) {
            s = IN;
            wc++;
        }
    }
    printf("cc=%d lc=%d wc=%d\n", cc, lc, wc);
    return 0;
}