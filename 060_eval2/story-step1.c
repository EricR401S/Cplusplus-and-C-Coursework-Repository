#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // throw error if input structure is violated
  if (argc != 2) {
    fprintf(stderr, "Usage: story-step1 StoryFileName\n");
    return EXIT_FAILURE;
  }

  // arg greater than 1 case - for loop
  // remember to close file, throw error if necessary

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  story_parser(f, NULL);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  /////////////////////////
  // free if I haven't yet

  return EXIT_SUCCESS;
}
