#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test_seq(int * array, size_t n, size_t right_answer) {
  size_t test_answer;
  test_answer = maxSeq(array, n);

  if (test_answer != right_answer) {
    printf("The test answer (%lu) is wrong, verus right answer (%lu)\n",
           test_answer,
           right_answer);
    printf("The array is ");
    for (int i = 0; i < n; i++) {
      printf("%d ", array[i]);
    }
    printf("\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  //int my_array[] = {};
  //test_seq(my_array, 0, 0);

  int my_array2[1] = {1};  //one element
  test_seq(my_array2, 1, 1);

  int my_array3[] = {-1, -3, -2, -1, -2};  //negative increase
  test_seq(my_array3, 5, 3);

  int my_array4[] = {0, 1, 2, 3, 4, 5};  //normal ascension
  test_seq(my_array4, 6, 6);

  int my_array5[] = {0, 0, 0, 1};  // equal streak
  test_seq(my_array5, 4, 2);

  int my_array6[] = {5, 4, 1, 0};  // descension
  test_seq(my_array6, 4, 1);

  int my_array7[] = {4, 5, 5, 6};  // middle equal streak
  test_seq(my_array7, 4, 2);

  int my_array8[] = {0, 0, 0};  // all equal
  test_seq(my_array8, 3, 1);

  int my_array9[] = {7, 8, 9, 10, 1, 2, 3};  //forgotten maximum
  test_seq(my_array9, 7, 4);

  int my_array10[] = {-8, -7, -6, -5};  // negative descension two
  test_seq(my_array10, 4, 4);

  int my_array11[] = {0, 5, 0, 5};  // alternation
  test_seq(my_array11, 4, 2);

  int my_array12[] = {1, 2, 3};  // forget the first or the last
  test_seq(my_array12, 3, 3);

  int my_array13[] = {0.6, 0.7, 1, 1.1};  // they just get converted to ints
  test_seq(my_array13, 4, 2);

  test_seq(NULL, 0, 0);

  int my_array15[] = {-3, 5, -1, -1, 2, -3, 4, -5};  // negative
  test_seq(my_array15, 6, 2);

  int my_array16[] = {-1, -2, -3};
  test_seq(my_array16, 3, 1);

  int my_array17[] = {-3, -2, -1, 0};
  test_seq(my_array17, 4, 4);
  //int my_array17[] = {-2147483648, -2147483647, -2147483649};
  //test_seq(my_array17, 3, 2);
  // doesn't pass run all

  int my_array18[1000] = {5};  // larger? sequences
  test_seq(my_array18, 1000, 1);

  return EXIT_SUCCESS;
}
