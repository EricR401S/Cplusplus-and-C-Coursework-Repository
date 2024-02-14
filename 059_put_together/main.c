#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

/* char * remove_newline(char * some_string) { */
/*   size_t str_size = strlen(some_string); */

/*   some_string[str_size - 1] = '\0'; */

/*   return some_string; */
/* } */

char * search_key(const char * some_str, kvarray_t * kvPairs) {
  // determines if string exists in kvPairs array

  for (size_t i = 0; i < kvPairs->size; i++) {
    if (strcmp(some_str, kvPairs->array[i]->key) == 0) {
      return kvPairs->array[i]->value;
    };
  }
  return NULL;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");

  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  counts_t * file_counts = createCounts();

  char * dynamic_string = NULL;
  size_t dynamic_str_size;

  while ((getline(&dynamic_string, &dynamic_str_size, f)) >= 0) {
    char * value = search_key(remove_newline(dynamic_string), kvPairs);

    if (value == NULL) {
      addCount(file_counts, NULL);
    }

    else {
      addCount(file_counts, value);
    }
    free(dynamic_string);
    dynamic_string = NULL;
  }
  free(dynamic_string);
  fclose(f);

  return file_counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)

  // check argc integrity

  if (argc < 2) {
    fprintf(stderr, "Usage: count_values kv_file.txt input_file.txtm");
    exit(EXIT_FAILURE);
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv_pairs = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv_pairs);
    //compute the output file name from argv[i] (call this outName)
    char * output_name = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * output = fopen(output_name, "w");

    //print the counts from c into the FILE f
    printCounts(c, output);

    //close f
    fclose(output);

    //free the memory for outName and c
    free(output_name);
    freeCounts(c);
  }

  //free the memory for kv
  freeKVs(kv_pairs);

  return EXIT_SUCCESS;
}
