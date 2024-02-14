#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotMatriz(FILE * m) {
  size_t char_num = 0;

  int row_counter = 0;

  int col_counter = 9;

  int c;

  char arr[10][11] = {0};

  // start to read characters

  while ((c = fgetc(m)) != EOF) {
    char_num++;

    if (c == 0xFF) {
      fprintf(stderr, "Use only ASCII characters in input file\n");
      exit(EXIT_FAILURE);
    }

    // check if it char_num exceeded 110 fail if that is the case
    if (char_num > 110) {
      fprintf(stderr, "Input file can have max 110 characters\n");
      exit(EXIT_FAILURE);
    }

    // if the char is a newline
    // and the row is not 10, fail it
    if ((c == '\n') && (row_counter != 10)) {
      fprintf(stderr, "No empty lines allowed in Input file\n");
      exit(EXIT_FAILURE);
    }

    // if the char is not a newline and the row is 10, fail it
    if ((c != '\n') && (row_counter == 10)) {
      fprintf(stderr,
              "Each line should have max 10 characters and a newline character, total of "
              "11\n");
      exit(EXIT_FAILURE);
    }

    // if the row > 9,
    //reset to 0
    if (row_counter > 9) {
      row_counter = 0;
      col_counter--;
      continue;
    }

    arr[row_counter][col_counter] = c;
    row_counter++;
  }
  // write a newline at row i, col 10
  for (int i = 0; i < 10; i++) {
    arr[i][10] = '\n';
  }
  // After reading the file
  if (char_num < 110) {
    fprintf(
        stderr,
        "The file cannot have less than 110 characters, 11 characters (10 non-newline "
        "and one newline) and 10 lines\n");
    exit(EXIT_FAILURE);
  }

  char arr2[111] = {0};
  int final_char_count = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      arr2[final_char_count] = arr[i][j];
      final_char_count++;
    }
  }
  arr2[110] = '\0';

  fprintf(stdout, "%s", arr2);
  return;
}

int main(int argc, char ** argv) {
  // If they gave too many or too little inputs

  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFile.txt\n");
    return EXIT_FAILURE;
  }

  // what if the file does not exist
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  rotMatriz(f);

  // file fails to close, might remove
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
