#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);  //prototype

void run_checker(unsigned x, unsigned y, unsigned right_answer) {
  if (power(x, y) != right_answer) {
    printf("The answer should have been %u", right_answer);

    exit(EXIT_FAILURE);
  }
}

int main() {
  run_checker(-2, 1, 4294967294);  // unsigned integer overflow
  run_checker(8, 0, 1);            // the zeroeth property of exponents
  run_checker(4, 1, 4);            //1 exponents
  //run_checker(2, 32, 0);           // cusp methodology
  run_checker(4, 3, 64);  //standard
  run_checker(0, 0, 1);
  //improper inputs
  run_checker(1, 1, 1);  // float has this representation in unsigned form
  // commented because it causes issues, unknown as to why
  run_checker('a', 1, 97);  //EXIT_FAILURE
  //run_checker(' ', ' ', EXIT_FAILURE); // no strings
  //run_checker(5, -1, EXIT_FAILURE);  // no negative exponents, eternal recursion
  return EXIT_SUCCESS;
}
