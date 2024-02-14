//#include <ctype.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "my_story_class.hpp"

std::string combine_dir_file_names(char * dir_name, std::string name_of_file) {
  // combines directory name with its file name

  std::string dirname(dir_name);

  std::string filename = dirname + "/" + name_of_file;

  return filename;
}

int directory_file_exists(char * some_arg, std::string name_of_file) {
  // Exits with error if file does not exists,
  // If it does exists, nothing happens.

  std::string filename = combine_dir_file_names(some_arg, name_of_file);

  char * cstr = new char[filename.length() + 1];
  std::strcpy(cstr, filename.c_str());

  // no leak if deleted here

  std::ifstream myfile(cstr);

  if (myfile.is_open()) {
    myfile.close();
    delete[] cstr;
    return 1;
  }

  else {
    myfile.close();
    delete[] cstr;
    std::cerr << "The File " + filename + "  does not exist. Unable to open file\n";
    return 0;
    // 7 allocs, 6 frees vs the 6 allocs and 6 frees of above
    // this is the first memory leak.
    //exit(EXIT_FAILURE);
  }

  return 0;
}

char * file_charname(char * dir_name, std::string name_of_file) {
  // Combines directory name with its file name
  // to produce a char * version of the full filename

  std::string dirname(dir_name);

  std::string filename = dirname + "/" + name_of_file;

  char * cstr = new char[filename.length() + 1];
  std::strcpy(cstr, filename.c_str());

  return cstr;
}

bool is_found(std::string search_string, const char other_c) {
  // Verifies if character is in search string

  std::size_t location = search_string.find(other_c);
  if (location != std::string::npos) {
    return true;
  }
  else {
    return false;
  }
}

bool is_declaration_requirement_met(std::string some_str) {
  // Checks if all minimum characters @, : and one
  // of N, W or L is present in the page declaration string
  // If there is no number before the @
  // and no file after the :
  std::string search_1 = "@:";
  std::string search_2 = "NWL";

  bool valid = false;

  std::size_t found = 10;

  for (size_t i = 0; i < search_1.size(); i++) {
    found = some_str.find(search_1[i]);

    if (found == std::string::npos) {
      valid = false;
      return valid;
    }
  }

  const char * converted_str = some_str.c_str();
  if (converted_str[0] == '@' || some_str.find(":") == some_str.size() - 1) {
    valid = false;
    //delete converted_str;
    return valid;
  }
  //delete converted_str;
  for (size_t i = 0; i < search_2.size(); i++) {
    found = some_str.find(search_2[i]);

    if (found != std::string::npos) {
      valid = true;
    }
  }

  return valid;
}

bool is_page_declaration(std::string story_line, char * dirname) {  // add directory argv
  // Returns true if line indicates a page declaration
  // false otherwise

  // checks minimum chars required in @: and one in NWL
  // and other behaviors
  if (!is_declaration_requirement_met(story_line)) {
    return false;
  }

  // next section

  // check digits

  size_t at_location = story_line.find("@");

  // this does not look at the largeness of the page number
  for (size_t i = 0; i < at_location; i++) {
    if (!isdigit(story_line[i])) {
      //std::cout << story_line[i] << " is a digit \n";
      return false;
    }
  }
  size_t new_counter = at_location + 1;

  if (story_line.substr(new_counter, 1) != "N" &&
      story_line.substr(new_counter, 1) != "W" &&
      story_line.substr(new_counter, 1) != "L") {
    //std::cout << story_line.substr(new_counter, 1) << "is the substr\n";
    return false;
  }
  new_counter++;

  if (story_line.substr(new_counter, 1) != ":") {
    //return false;
    //std::cout << story_line.substr(new_counter, 1) << " is not a colon\n";
    return false;
  }

  new_counter++;

  std::string filename = story_line.substr(new_counter);
  //std::cout << filename << "is my finelname\n";
  if (!directory_file_exists(dirname, filename)) {
    std::cout << filename << " is not a valid filename\n";
    return false;
  }

  return true;
}
