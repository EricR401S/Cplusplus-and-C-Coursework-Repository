#include <stdlib.h>

void main() {
  int x = 5;
  const int * p = &x;
  int * const * q = &p;
}
