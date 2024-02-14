#include <stdlib.h>

int main(void) {
  size_t n = 2;  //originally 4
  int * x = malloc(sizeof(n));
  for (size_t i = 0; i < n; i++) {
    x[i] = i;
  }
  free(x);
  return 0;
}
