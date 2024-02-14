#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if ((array == NULL)) {
    printf("Array cannot be empty\n");
    //return EXIT_FAILURE;  //already tried 0
    return 0;
  }

  else if (n == 0) {
    //printf("N cannot be 0\n");
    //return EXIT_FAILURE;  // already tried 0
    return 0;
  }

  else if (n == 1) {
    return 1;
  }

  else {
    int max_c = 1;

    int c = 1;

    int curr_val = array[0];

    for (size_t i = 1; i < n;
         i++) {  //changed i to 1, not 0, and then type from int to size_t
      if (array[i] > curr_val) {  //took out curr val
        c++;
      }

      else {
        c = 1;
      }

      if (c > max_c) {
        max_c = c;
      }

      curr_val = array[i];

    }  //close for loop

    return max_c;
  }
}
