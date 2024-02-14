#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t string_exists(counts_t * some_counts_t, const char * name) {
  // checks if the string exists and returns index
  size_t internal_warning_counter = 0;
  for (size_t i = 0; i < some_counts_t->array_size; i++) {
    if (some_counts_t->one_count_array[i].string_id == NULL) {
      internal_warning_counter++;
      assert(internal_warning_counter == 1);
      continue;
    }

    if (strcmp(name, some_counts_t->one_count_array[i].string_id) == 0) {
      return i;
    }
  }

  return 0;
}
counts_t * createCounts(void) {
  //WRITE ME

  //The first, createCounts should allocate memory for a counts_t structure, and initialize
  //it to represent that nothing has been counted yet.

  counts_t * new_counts_arr = malloc(1 * sizeof(*new_counts_arr));
  // the stuct in the one c array is just a pointer to null
  new_counts_arr->array_size = 1;
  new_counts_arr->unknowns = 0;
  new_counts_arr->one_count_array = malloc(1 * sizeof(*new_counts_arr->one_count_array));
  new_counts_arr->one_count_array->count = 0;
  //new_counts_arr->one_count_array->string_id = malloc(sizeof(*(new_counts_arr->one_count_array->string_id)));
  new_counts_arr->one_count_array->string_id = NULL;
  return new_counts_arr;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //The next function, addCount, should increment the count for the corresponding name.  Note
  //that name will be NULL in the case of something that is unknown, so your code must account
  //for this case.

  size_t name_exists = 0;
  if (name == NULL) {
    c->unknowns++;
    return;
    //c->one_count_array->count++;
  }

  else {
    name_exists = string_exists(c, name);
    // if it exists, update the counts
    if (name_exists > 0) {
      c->one_count_array[name_exists].count++;
    }

    else {
      assert(name_exists == 0);
      // allocate space, create new entry, initialize and so forth
      c->array_size++;
      c->one_count_array =
          realloc(c->one_count_array, c->array_size * sizeof(*c->one_count_array));
      c->one_count_array[c->array_size - 1].count = 1;
      c->one_count_array[c->array_size - 1].string_id = strdup(name);
    }
  }

  return;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME

  /* The third function, printCounts takes a counts_t and prints that information to  */
  /* the FILE outFile. Recall from the description of the entire problem, that this  */
  /* function should print in the format: */

  /* Captain: 1 */
  /* Commander: 2 */
  /* Lt. Commander: 1 */
  /* <unknown> : 1 */

  /* These should appear in the order that the name is first added, with unknown always */
  /* appearing last. */

  /* ***If there are no unknown values, you should not print a line for unknown.  That */
  /* is, you should NEVEr print */
  /* <unknown> : 0 */

  // something about a file

  if (outFile == NULL) {
    perror("Could not open file or file does not exist");
    exit(EXIT_FAILURE);
  }

  if ((c->array_size > 1)) {
    for (size_t i = 1; i < c->array_size; i++) {
      fprintf(outFile,
              "%s: %zu\n",
              c->one_count_array[i].string_id,
              c->one_count_array[i].count);
    }

    if (c->unknowns > 0) {
      fprintf(outFile, "<unknown> : %zu\n", c->unknowns);
    }
  }

  else if ((c->array_size == 1) && c->unknowns > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknowns);
  }

  return;
}

void freeCounts(counts_t * c) {
  //WRITE ME
  if (c->array_size > 1) {
    // free everything
    for (size_t i = 1; i < c->array_size; i++) {
      //
      free(c->one_count_array[i].string_id);
    }
    free(c->one_count_array);

    free(c);
  }

  else {
    free(c);  // might need to free string id
  }

  return;
}
