#ifndef __T_STORY_H___
#define __T_STORY_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//YOUR CODE GOES HERE!

class Page {
  // This class stores the contents
  // and page of a story page
  // It is the base for all the
  // other pages
 protected:
  size_t num;

  std::string content;

 public:
  // add page constructor
  // Page() :

  virtual void print_page() const = 0;
};

class Story {
  // this is a story class that stores the
  // the story pages

 protected:
  std::vector<Page *> story_pages;

 public:
  Story(){};

  void add_page(Page * some_page) { story_pages.push_back(some_page); }

  //print
};

// Functions

std::string combine_dir_file_names(char * dir_name, std::string name_of_file);

int directory_file_exists(char * some_arg, std::string name_of_file);

char * file_charname(char * dir_name, std::string name_of_file);

bool is_declaration_requirment_met(std::string some_str);
bool is_page_declaration(std::string story_line, char * dirname);

#endif
