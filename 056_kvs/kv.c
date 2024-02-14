#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * remove_newline(char * some_string) {
  size_t str_size = strlen(some_string);

  some_string[str_size - 1] = '\0';

  return some_string;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");

  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  kvarray_t * dynamic_kv_arr = malloc(sizeof(kvarray_t));
  dynamic_kv_arr->size = 0;
  dynamic_kv_arr->array = NULL;
  char * dynamic_string = NULL;
  size_t dynamic_str_size;
  size_t kv_counter = 0;  // dynamic array size
  size_t split_counter = 0;

  while ((getline(&dynamic_string, &dynamic_str_size, f)) >= 0) {
    char * copy = strdup(dynamic_string);

    // splitting by only one '=' delimiter, as it divides the key value pairs

    char * found;

    //while (((found = strsep(&copy, "=")) != NULL) && (split_counter != 1)) {
    // What is in found will be the key, and
    // the pointer onwards in copy will be the value
    //split_counter++;
    //}
    while (split_counter != 1) {
      // What is in found will be the key, and
      // the pointer onwards in copy will be the value
      found = strsep(&copy, "=");
      split_counter++;
    }
    split_counter = 0;  //reset to 0 for next use

    kvpair_t * current_pair = malloc(sizeof(kvpair_t));
    current_pair->key = found;
    copy = remove_newline(copy);
    current_pair->value = copy;

    // ask Zeck, I don't think we free copy or found, as it will erase everything

    kv_counter++;
    dynamic_kv_arr->array =
        realloc(dynamic_kv_arr->array, (kv_counter * sizeof(*(dynamic_kv_arr->array))));
    //
    dynamic_kv_arr->array[kv_counter - 1] = current_pair;

    // back to house more strings
    free(dynamic_string);
    dynamic_string = NULL;
  }
  free(dynamic_string);
  dynamic_kv_arr->size = kv_counter;
  fclose(f);
  return dynamic_kv_arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    free(pairs->array[i]->key);
    //free(pairs->array[i]->value); - shares same memory as the original strings
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  //Third, write printKVs which should take a kvarray_t *, and print out

  //"key = '%s' value = '%s'\n"
  //for each key/value pair in the array, with the first %s being whatever the key is,
  //and the second being whatever value (e.g., key = 'Jean Luc Picard' value = 'Captain'

  for (size_t i = 0; i < pairs->size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME

  //Finally, write the lookupValue function, which takes a kvarray_t * and a char * (string).
  //The char * that is passed in represents a key.  This function searches the kvarray_t
  //for a matching key, and if found, returns the corresponding value.  If no match is found,
  //this function returns NULL.

  for (size_t i = 0; i < pairs->size; i++) {
    if ((strcmp(key, pairs->array[i]->key)) == 0) {
      return pairs->array[i]->value;
    }
  }

  return NULL;
}
