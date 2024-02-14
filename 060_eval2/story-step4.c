#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // throw error if input structure is violated
  if ((argc < 3) || (argc > 4)) {
    fprintf(stderr, "Usage: -n (optional) story-step3 CategoryFileName StoryFileName\n");
    return EXIT_FAILURE;
  }

  // arg greater than 1 case - for loop
  // remember to close file, throw error if necessary

  size_t word_index = 1;
  size_t story_index = 2;

  if (argc == 4) {
    word_index++;
    story_index++;
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "The allowable option is '-n', which is case sensitive \n");
      return EXIT_FAILURE;
    }
  }

  FILE * f = fopen(argv[word_index], "r");

  if (f == NULL) {  // code repeats because of valgrind issues
    //fclose(f);
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  catarray_t * cats = category_parser(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }

  f = fopen(argv[story_index], "r");

  if (f == NULL) {
    fclose(f);
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  if (argc == 4) {
    story_parser_v2(f, cats, 1);
  }

  else {
    story_parser_v2(f, cats, 0);
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  /////////////////////////
  // free if I haven't yet

  free_cats(cats);

  return EXIT_SUCCESS;
}
