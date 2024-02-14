#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//any functions you want your main to use

void free_cats(catarray_t * cats);

void call_error(bool condition, char * message, FILE * f);

void free_cats(catarray_t * cats);

void category_checker(char * s, catarray_t * cats, FILE * f);

void create_new_category(catarray_t * cats, char * cat_string, char * word_string);

void add_word_to_category(catarray_t * cats, size_t found_index, char * word_string);

catarray_t * category_parser(FILE * f);

bool is_number(char * recorded_string);

bool searchCategory(char * category, catarray_t * cats);

void story_parser(FILE * f, catarray_t * cats);

char * findCategoryWord(char * category, catarray_t * cats);

bool can_backreference(size_t backref_number, catarray_t * used_words);

char * backreference(size_t backref_number, catarray_t * used_words);

catarray_t * initialize_UsedWords();

char * madlibs(char * recorded_str, catarray_t * cats, catarray_t * UsedWords);

void remove_word(char * category, char * chosen_word, catarray_t * cats);

void story_parser_v2(FILE * f, catarray_t * cats, int option_n);

#endif
