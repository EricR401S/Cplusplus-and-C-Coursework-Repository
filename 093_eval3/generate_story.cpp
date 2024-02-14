//#include <ctype.h>

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

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

bool are_digits_until_position(std::string some_string, size_t start, size_t position) {
  // Returns true if every character excluding the position is a digit

  for (size_t i = start; i < position; i++) {
    //std::cout << some_string[i];
    if (!isdigit(some_string[i])) {
      //std::cout << "Ended here\n";
      return false;
    }
  }
  //std::cout << "Ended here\n";
  return true;
}

bool is_page_declaration(std::string story_line,
                         char * dirname) {  // add directory argv
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
  // for (size_t i = 0; i < at_location; i++) {
  //   if (!isdigit(story_line[i])) {
  //     //std::cout << story_line[i] << " is a digit \n";
  //     return false;
  //   }
  // }

  if (!are_digits_until_position(story_line, 0, at_location)) {
    return false;
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

// change to return to page eventually

std::string file_to_string(char * dir_name, std::string name_of_file) {
  // Returns the contents of the file in a string

  char * page_path = file_charname(dir_name, name_of_file);
  std::string page_body;
  std::string line;
  std::ifstream myfile(page_path);
  if (myfile.is_open()) {
    delete[] page_path;
    while (getline(myfile, line)) {
      page_body += line + "\n";
    }
  }
  return page_body;
}
void parse_declaration(std::string story_line, char * dirname) {
  // Parses the context of the declaration page line
  // and returns the page object with the details
  // referenced by the contents.

  // Since this is a declaration page, the body of the text file
  // is in a string.

  std::size_t at_location = story_line.find("@");

  std::string page_number_str = story_line.substr(0, at_location);

  size_t page_num = 111;
  try {
    page_num = strtoul(page_number_str.c_str(), NULL, 10);
    std::cout << " My declaration page num is " << page_num << "\n";
  }

  catch (const std::out_of_range & numtoolarge) {
    std::cerr << "Error in declaration line : number is too large.\n";
    exit(EXIT_FAILURE);
  }

  std::size_t moving_counter = at_location + 1;

  std::string page_type = story_line.substr(moving_counter, 1);

  moving_counter += 2;

  std::string filename = story_line.substr(moving_counter);

  //std::string page_contents = file_to_string(dirname, filename);
  // std::cout << " my page number in " << story_line << " is " << page_num
  //           << "\n My page type is " << page_type << "\n My filename is " << filename
  //           << "\n The page content is : \n"
  //           << page_contents << "DONE\n";
  //std::cout << page_contents;

  /////////////////////////////////////////////////////////////////////
  // add page construction and change return // uncomment my try catch and page num//////////////////////////////////////////
  return;
}

Page * parse_declaration_page(std::string story_line, char * dirname) {
  // Parses the context of the declaration page line
  // and returns the page object with the details
  // referenced by the contents.

  // Since this is a declaration page, the body of the text file
  // is in a string.

  std::size_t at_location = story_line.find("@");

  std::string page_number_str = story_line.substr(0, at_location);

  size_t page_num = 111;
  try {
    page_num = strtoul(page_number_str.c_str(), NULL, 10);
    std::cout << " My declaration page num is " << page_num << "\n";
  }

  catch (const std::out_of_range & numtoolarge) {
    std::cerr << "Error in declaration line : number is too large.\n";
    exit(EXIT_FAILURE);
  }

  std::size_t moving_counter = at_location + 1;

  std::string page_type = story_line.substr(moving_counter, 1);

  moving_counter += 2;

  std::string filename = story_line.substr(moving_counter);

  std::string page_body = file_to_string(dirname, filename);

  //return new Page(page_num, page_body);

  if (page_type == "N") {
    return new ChoicePage(page_body, page_num);
  }

  else if (page_type == "W") {
    return new TerminalPage(page_body, page_num, true);
  }

  else {
    return new TerminalPage(page_body, page_num, false);
  }
}

bool is_choice_page(std::string story_line) {
  // Returns true if the line indicates a proper format of a choice page

  size_t count_of_colon = 0;
  const char * cstr = story_line.c_str();

  for (size_t m = 0; m < story_line.size(); m++) {
    if (cstr[m] == ':') {
      count_of_colon++;
    }
  }

  if (count_of_colon < 2 || cstr[0] == ':') {
    return false;
  }

  //checking if the colons are preceded by numbers

  size_t colon_first_position = story_line.find(":");

  size_t colon_second_position = story_line.find(":", colon_first_position + 1);

  // std::string page_num_str = story_line.substr(0, colon_first_position);

  // std::string destination_num_str = story_line.substr(
  //     colon_first_position + 1, colon_second_position - colon_first_position - 1);

  // std::string choice_text = "";

  // if (story_line.size() - 1 != colon_second_position) {
  //   choice_text = story_line.substr(colon_second_position + 1);
  // }
  // std::cout << " iscchoice-- the page num is -" << page_num_str
  //           << "-, and the destination is -" << destination_num_str
  //           << "-and my choice text is -" << choice_text
  //           << "-, got it? The colo first position is -" << colon_first_position
  //           << "-, andf the second position is -" << colon_second_position << "-\n";

  if (!are_digits_until_position(story_line, 0, colon_first_position) ||
      !are_digits_until_position(
          story_line, colon_first_position + 1, colon_second_position) ||
      cstr[colon_first_position + 1] == ':') {
    return false;
  }

  return true;
}

void parse_choice_line(std::string story_line,
                       Story & a_story) {  // add story class as arg;
  // Returns nothing, adds choice string to existing page
  size_t colon_first_position = story_line.find(":");

  size_t colon_second_position = story_line.find(":", colon_first_position + 1);

  std::string page_num_str = story_line.substr(0, colon_first_position);

  std::string destination_num_str = story_line.substr(
      colon_first_position + 1, colon_second_position - colon_first_position - 1);

  size_t page_num = 111;
  size_t destination_num = 111;
  try {
    page_num = strtoul(page_num_str.c_str(), NULL, 10);
    destination_num = strtoul(destination_num_str.c_str(), NULL, 10);
  }

  catch (const std::out_of_range & numtoolarge) {
    std::cerr
        << "Error in choice line : one or both of the numbers is or are too large.\n";
    exit(EXIT_FAILURE);
  }

  std::string choice_text = "";

  if (story_line.size() - 1 != colon_second_position) {
    choice_text = story_line.substr(colon_second_position + 1);
  }
  std::cout << " iscchoice-- the page num is -" << page_num      //page_num_str
            << "-, and the destination is -" << destination_num  //destination_num_str
            << "-and my choice text is -" << choice_text
            << "-, got it? The colo first position is -" << colon_first_position
            << "-, andf the second position is -" << colon_second_position << "-\n";

  // add the choice

  a_story.add_choice(choice_text, page_num, destination_num);
}

bool is_whitespace_line(std::string line) {
  // Return true if whitespace is a line

  // run checks here

  size_t line_sz = line.size();

  if (line_sz == 0) {
    // had only one newline when used with getline
    //std::cout << "It has only a newline" << std::endl;
    return true;
  }

  size_t whitespace_counter = 0;
  for (size_t i = 0; i < line_sz; i++) {
    if (line[i] == ' ') {
      whitespace_counter++;
    }
  }

  if (whitespace_counter == line_sz) {
    return true;
  }

  else {
    return false;
  }

  return false;
}
