#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // throw error if input structure is violated
  if (argc != 3) {
    fprintf(stderr, "Usage: story-step3 CategoryFileName StoryFileName\n");
    return EXIT_FAILURE;
  }

  // arg greater than 1 case - for loop
  // remember to close file, throw error if necessary

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {  // code repeats because of valgrind issues
    //fclose(f);
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  catarray_t * cats = category_parser(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  f = fopen(argv[2], "r");

  if (f == NULL) {
    fclose(f);
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  story_parser_v2(f, cats, 0);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  /////////////////////////
  // free if I haven't yet

  free_cats(cats);

  return EXIT_SUCCESS;
}
