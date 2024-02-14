#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "my_story_class.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "User Error : No more than one directory can be provided\n";
    return EXIT_FAILURE;
  }

  // checking if directory's file exists

  if (!directory_file_exists(argv[1], "story.txt")) {
    exit(EXIT_FAILURE);
  }

  // create story object
  Story my_story = Story();

  // assuming the file exists, now we proceed to parse
  // the lines in story.txt

  char * story_file_path = file_charname(argv[1], "story.txt");

  bool line_failure = false;
  std::string line;
  std::ifstream myfile(story_file_path);
  if (myfile.is_open()) {
    delete[] story_file_path;
    while (getline(myfile, line)) {
      // these functions return false if line does not satisfy format
      bool declaration_check = is_page_declaration(line, argv[1]);
      bool choice_check = is_choice_page(line);
      bool whitespace_check = is_whitespace_line(line);

      // evaluate what to do with the lines based on the checks
      // create pages or add choices to pages or identify errors
      if (declaration_check) {
        Page * my_page = parse_declaration_page(line, argv[1]);
        my_story.add_page(my_page);
        continue;
      }

      else if (choice_check) {
        parse_choice_line(line, my_story);
      }

      else if (whitespace_check) {  // not an error, just skip
        continue;
      }
      else {
        // set all bools to false to error out
        // because the line failed to satisfy the above checks
        declaration_check = false;
        choice_check = false;
        whitespace_check = false;
        line_failure = true;
        break;
      }
    }
  }
  myfile.close();
  if (line_failure) {
    std::cerr << "The line " + line +
                     " in story.txt did not follow the proper format for being a "
                     "declaration or choice page. In the case of the declaration, the "
                     "error may have also been the non-existance of the page file.\n";

    exit(EXIT_FAILURE);
  }

  //step 1 : print the story
  my_story.print_story();

  return EXIT_SUCCESS;
}
