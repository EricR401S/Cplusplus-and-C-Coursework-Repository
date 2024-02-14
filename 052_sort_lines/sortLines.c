#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printStrArray(char ** str_array, size_t size) {
  // prints array and frees the memory
  for (size_t i = 0; i < size; i++) {
    printf("%s", str_array[i]);
    free(str_array[i]);  //
  }
  free(str_array);
}

void file_to_string_array(FILE * f) {
  // creates string array for printing
  // and frees the memort
  char ** dynamic_array = NULL;  //
  char * dynamic_string = NULL;
  size_t dynamic_str_size;
  size_t i = 0;  // dynamic array size
  size_t line_counter = 0;

  while ((getline(&dynamic_string, &dynamic_str_size, f)) >= 0) {
    dynamic_array = realloc(dynamic_array, (i + 1) * sizeof(*dynamic_array));

    // now dynamic array points to a diff block of memory with more boxes

    dynamic_array[i] = dynamic_string;
    dynamic_string = NULL;
    i++;
    line_counter++;
  }
  free(dynamic_string);

  sortData(dynamic_array, line_counter);

  printStrArray(dynamic_array, line_counter);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  // arg 1 case
  // remember to close file, throw error if necessary
  if (argc == 1) {
    file_to_string_array(stdin);
  }

  // arg greater than 1 case - for loop
  // remmeber to close file, throw error if necessary
  else {
    for (int i = 1; i < argc; i++) {
      FILE * input_file = fopen(argv[i], "r");
      if (input_file == NULL) {
        fprintf(stderr, "File number %d is the problem", i);
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      // converting file to array for printing
      file_to_string_array(input_file);

      if (fclose(input_file) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
