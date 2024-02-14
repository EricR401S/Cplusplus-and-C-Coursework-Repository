#include "rand_story.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void call_error(bool condition, char * message, FILE * f) {
  // Prints error to stderr if condition is satisfied
  // and exits the program
  if (condition) {
    fprintf(stderr, "Error : %s\n", message);
    fclose(f);
    exit(EXIT_FAILURE);
  }

  else {
    return;
  }
}

void free_cats(catarray_t * cats) {
  // free all the memory incurred by the catarray_t mallocs

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

void category_checker(char * s, catarray_t * cats, FILE * f) {
  // Validates if a category has the necessary newline or colon
  // per line. If not, exit program with Failure status.
  size_t len = strlen(s);
  bool colon_found = 0;
  bool newline_found = 0;
  for (size_t i = 0; i < len; i++) {
    if (s[i] == ':') {
      colon_found = true;
    }
    if (s[i] == '\n') {
      newline_found = true;
    }
  }
  if ((newline_found == false || colon_found == false)) {
    free(s);
    if (cats->n == 0) {
      free(cats);
    }
    else {
      free_cats(cats);
    }
  }
  call_error(
      (newline_found == false || colon_found == false), "Colon or newline is absent", f);
}

char * parse_cat_content(char * str,
                         char * target_string,
                         char delimiter,
                         size_t * counter_pointer,
                         FILE * f) {
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

  target_string = realloc(target_string, ((sz + 1) * sizeof(*target_string)));
  target_string[sz] = '\0';
  return target_string;
}

void create_new_category(catarray_t * cats, char * cat_string, char * word_string) {
  // Initializes a new category by making the necessary mallocs
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
  // Adds a word to the specified category and updates the n_words field
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
    category_checker(dynamic_string, cats, f);
    cat_string = parse_cat_content(dynamic_string, cat_string, ':', &cat_counter, f);

    word_counter = cat_counter + 1;
    word_string = parse_cat_content(dynamic_string, word_string, '\n', &word_counter, f);

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
        add_word_to_category(cats, found_index, word_string);
      }
      else {  //if cat does not exist, create new entry
        create_new_category(cats, cat_string, word_string);
      }
    }
    free(dynamic_string);
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

bool is_number(char * recorded_string) {
  // Returns true if the contents of the string
  // can be converted to a number via atoi
  bool is_number = true;
  size_t sz = strlen(recorded_string);
  for (size_t i = 0; i < sz; i++) {
    if (isdigit(recorded_string[i]) == 0) {
      is_number = false;
      return is_number;
    }
  }
  return is_number;
}

bool searchCategory(char * category, catarray_t * cats) {
  // Return true if category exists, false otherwise
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(category, cats->arr[i].name) == 0) {
      return true;  // might have to check for number of words in category
    }
  }
  return false;
}

char * findCategoryWord(char * category, catarray_t * cats) {
  // Return pointer to chosen word from category
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(category, cats->arr[i].name) == 0) {
      size_t found = rand() % cats->arr[i].n_words;

      while (found >= cats->arr[i].n_words) {
        found = rand() % cats->arr[i].n_words;
      }
      return cats->arr[found].name;
    }
  }
  return NULL;
}

bool can_backreference(size_t backref_number, catarray_t * used_words) {
  //Returns true if a backreference is possible with used_words
  if ((backref_number <= used_words->arr[0].n_words) && (backref_number != 0)) {
    return true;
  }

  else {
    return false;
  }
}

char * backreference(size_t backref_number, catarray_t * used_words) {
  //Returns char * for word from used_words corresponding
  //to backref_number

  size_t backref_choice_ind = used_words->arr[0].n_words - backref_number;

  return used_words->arr[0].words[backref_choice_ind];
}

void story_parser(FILE * f, catarray_t * cats) {
  // Parses and prints the parsed story as file is read
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
        //sz = 0;
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

catarray_t * initialize_UsedWords() {
  //Initializes a single catarray_t to hold the UsedWords
  // category_t
  catarray_t * UsedWords = malloc(sizeof(*UsedWords));
  UsedWords->n = 1;
  UsedWords->arr = NULL;
  UsedWords->arr = realloc(UsedWords->arr, 1 * sizeof(*UsedWords->arr));
  char * name = malloc(10 * sizeof(*name));
  char s[] = "UsedWords";
  for (size_t j = 0; j < strlen(s); j++) {
    name[j] = s[j];
  }

  UsedWords->arr[0].name = name;
  UsedWords->arr[0].n_words = 0;
  UsedWords->arr[0].words = NULL;
  return UsedWords;
}

char * madlibs(char * recorded_str, catarray_t * cats, catarray_t * UsedWords) {
  // Returns char * to chosen string, but NULL if the backreference fails or category of interest is not found
  bool str_is_number = is_number(recorded_str);
  //bool found_error = false;
  if (str_is_number) {
    size_t bk_number = atoi(recorded_str);
    // This is a backreference
    if (can_backreference(bk_number, UsedWords)) {
      // return the pointer to the word
      return backreference(bk_number, UsedWords);
    }
    else {
      return NULL;  //might cause issues
    }
  }
  else {
    //This is category

    if (cats == NULL) {
      return (char *)chooseWord(recorded_str, cats);
    }

    else if (searchCategory(recorded_str, cats)) {
      // return a word
      return (char *)chooseWord(recorded_str, cats);
    }
    else {
      return NULL;
    }
  }
}

void remove_word(char * category, char * chosen_word, catarray_t * cats) {
  // Removes word from the category_t.words and updates its size n_words
  // This is done in coordination with the option -n when passed
  // as a command line option
  size_t master_i = 0;
  size_t master_j = 0;
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, category) == 0) {
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        if (strcmp(cats->arr[i].words[j], chosen_word) == 0) {
          master_i = i;
          master_j = j;
          //break;  //in case duplicates should not be erased
        }
      }
    }
  }

  // start to free
  free(cats->arr[master_i].words[master_j]);
  cats->arr[master_i].words[master_j] = NULL;

  if (master_j == cats->arr[master_i].n_words - 1) {
    return;
  }

  else {
    cats->arr[master_i].words[master_j] =
        cats->arr[master_i].words[cats->arr[master_i].n_words - 1];
    cats->arr[master_i].words[cats->arr[master_i].n_words - 1] = NULL;
    return;
  }
  return;
}

void story_parser_v2(FILE * f, catarray_t * cats, int option_n) {
  // Parses and prints parsed story as the file is read.
  // It allows the option to not reuse words
  catarray_t * UsedWords = initialize_UsedWords();
  char * s = NULL;
  size_t sz = 0;
  int c;
  bool record = false;
  //triggered by bad referencing or inexistent categories
  bool special_error = false;
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
        char * choice = madlibs(s, cats, UsedWords);
        if (choice == NULL) {
          special_error = true;
          break;
        }
        else {
          printf("%s", choice);
          add_word_to_category(UsedWords, 0, strdup(choice));
          if ((option_n == 1) && (is_number(s) == false)) {
            remove_word(s, choice, cats);
          }
          free(s);
          s = NULL;
          sz = 0;
          continue;
        }
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

  if ((underscore_count % 2 != 0) || (special_error == true)) {
    free(s);
    free_cats(cats);
    free_cats(UsedWords);
    fclose(f);
    fprintf(stderr,
            "You did not enclose a category within underscores, or you have a category "
            "that doesn't exist, or you have an improper backreference number\n");
    exit(EXIT_FAILURE);
  }

  free_cats(UsedWords);

  return;
}
