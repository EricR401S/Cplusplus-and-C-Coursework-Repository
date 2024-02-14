#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int max_finder(int * some_array, int end) {
  //find max value in array and return index
  int max_index = 0;
  for (int i = 1; i < end; i++) {
    if (some_array[i] > some_array[max_index]) {
      max_index = i;
    }
  }
  return max_index;
}

int key_finder(FILE * f) {
  int c;
  int letter_frequency[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      // this is the position now
      c -= 'a';
      letter_frequency[c] += 1;
    }
    else {
      continue;
    }
  }
  // which is e?
  char secret_e;
  int maybe_e_index = max_finder(letter_frequency, 26);
  secret_e = maybe_e_index + 'a';
  int key = (secret_e - 'e');
  return key;
}

void encrypt(FILE * f, int key) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      c += key;
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  //int key = atoi(argv[1]);
  //if (key == 0) {
  //fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
  //return EXIT_FAILURE;
  //}
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = key_finder(f);
  if ((key < 0)) {
    key = key + 26;
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printf("%d\n", key);
  return EXIT_SUCCESS;
}
