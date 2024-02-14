#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  // some dynamic array (char **)resized by realloc
  // some dynamic string (char pointer) resized by realloc

  if (argc == 0) {
    //do something
    char * string = NULL;
    size_t size = 0;

    ssize_t my_str_length;

    while ((my_str_length = getline(&string, &size, stdin)) >= 0) {
      // not sure about conditional, given empty inputs
      printf("My string is : %s\n", string);
      free(string);
      string = NULL;
    }
  }

  return EXIT_SUCCESS;
}
