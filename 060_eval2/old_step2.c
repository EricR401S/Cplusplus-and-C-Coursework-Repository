#include "rand_story.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void call_error(bool condition, char * message) {
  // Prints error to stderr if condition is satisfied
  // and exits the program
  if (condition) {
    fprintf(stderr, "Error : %s\n", message);
    exit(EXIT_FAILURE);
  }

  else {
    return;
  }
}

char * parse_cat_content(char * str,
                         char * target_string,
                         char delimiter,
                         size_t * counter_pointer) {
  // Return string if there are contents to parse
  // Exit program with error otherwise
  target_string = NULL;
  size_t sz = 0;
  while (str[*counter_pointer] != delimiter) {
    sz++;
    target_string = realloc(target_string, (sz * sizeof(*target_string)));
    target_string[sz - 1] = str[*counter_pointer];
    (*counter_pointer)++;
  }
  if (sz == 0) {
    free(str);
    free(target_string);
  }
  call_error((sz == 0), "No category or word found");
  target_string = realloc(target_string, ((sz + 1) * sizeof(*target_string)));
  target_string[sz] = '\0';
  return target_string;
}

void create_new_category(catarray_t * cats, char * cat_string, char * word_string) {
  cats->n++;
  cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
  cats->arr[cats->n - 1].name = cat_string;
  cats->arr[cats->n - 1].n_words = 1;
  cats->arr[cats->n - 1].words =
      malloc(cats->arr[cats->n - 1].n_words * sizeof(*cats->arr[cats->n - 1].words));
  cats->arr[cats->n - 1].words[cats->arr[cats->n - 1].n_words - 1] = word_string;
  return;
}

void add_word_to_category(catarray_t * cats, size_t found_index, char * word_string) {
  cats->arr[found_index].n_words++;
  cats->arr[found_index].words =
      realloc(cats->arr[found_index].words,
              cats->arr[found_index].n_words * sizeof(*cats->arr[found_index].words));
  cats->arr[found_index].words[cats->arr[found_index].n_words - 1] = word_string;
  return;
}

catarray_t * category_parser(FILE * f) {
  // parses the category file to create a catarray_t
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  size_t cat_counter = 0;
  size_t word_counter = 0;
  char * cat_string = NULL;
  char * word_string = NULL;
  char * dynamic_string = NULL;
  size_t dynamic_str_size = 0;

  while ((getline(&dynamic_string, &dynamic_str_size, f)) >= 0) {
    // parse both the category and word
    cat_string = parse_cat_content(dynamic_string, cat_string, ':', &cat_counter);

    word_counter = cat_counter + 1;
    word_string = parse_cat_content(dynamic_string, word_string, '\n', &word_counter);

    // search function, if there, add word
    // if not create category
    if (cats->n == 0) {
      create_new_category(cats, cat_string, word_string);
    }
    else {
      //cats->n is greater than 0
      // search cats->arr for category
      bool found = false;
      size_t found_index = 0;
      for (size_t i = 0; i < cats->n; i++) {
        if (strcmp(cat_string, cats->arr[i].name) == 0) {
          // check if word exists
          found = true;
          found_index = i;
          free(cat_string);
        }
      }
      if (found == true) {
        // search for word in found category
        for (size_t j = 0; j < cats->arr[found_index].n_words; j++) {
          if (strcmp(word_string, cats->arr[found_index].words[j]) == 0) {
            // check if word exists
            free(word_string);
            word_string = NULL;
          }
        }
        if (word_string != NULL) {
          add_word_to_category(cats, found_index, word_string);
        }
      }
      else {  //if cat does not exist, create new entry
        create_new_category(cats, cat_string, word_string);
      }
    }
    dynamic_string = NULL;
    cat_string = NULL;
    word_string = NULL;
    cat_counter = 0;
    word_counter = 0;
    // set cat string and word string to Null
  }
  free(dynamic_string);  //  even if it did nto find a string
  return cats;
}

void free_cats(catarray_t * cats) {
  // free all the memory incurred by the category array

  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].name);

    free(cats->arr[i].words);
  }
  free(cats->arr);

  free(cats);
}
void story_parser(FILE * f, catarray_t * cats) {
  char * s = NULL;
  size_t sz = 0;
  int c;
  bool record = false;
  size_t underscore_count = 0;
  while ((c = fgetc(f)) != EOF) {
    if (c == '_') {
      underscore_count++;

      if (record == false) {
        // start to record string
        record = true;
        continue;
        // purposely ignore the first '_'
      }
      // assuming the first condition doesn't hit
      // finish recording the word to find it
      else if (record == true) {
        record = false;
        sz++;
        s = realloc(s, sz * sizeof(*s));
        s[sz - 1] = '\0';
        printf("%s", chooseWord(s, cats));
        free(s);
        s = NULL;
        continue;
      }
    }

    if (record == false) {
      printf("%c", c);  // cast if necessary
    }
    else {
      // recording the category string
      sz++;
      s = realloc(s, sz * sizeof(*s));
      s[sz - 1] = c;
    }
  }

  if (underscore_count % 2 != 0) {
    free(s);
    fprintf(stderr, "You did not enclose a category within underscores");
    exit(EXIT_FAILURE);
  }

  return;
}
