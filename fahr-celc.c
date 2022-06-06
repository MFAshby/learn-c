#include <stdio.h>

/* print farenheight-celcius 
conversion table for 0, 20, ...300 */
int main() {
  for (float fahr=0.0;
       fahr<=300.0;
       fahr+=20.0) {
    printf("%3.0f %6.1f\n",
      fahr,
      (5.0/9.0)*(fahr-32.0));
  }
}
