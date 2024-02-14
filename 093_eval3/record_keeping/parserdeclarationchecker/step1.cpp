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

  // assuming the file exists, now we proceed to parse
  // the lines in story.txt

  char * story_file_path = file_charname(argv[1], "story.txt");

  bool line_failure = false;
  std::string line;
  std::ifstream myfile(story_file_path);
  if (myfile.is_open()) {
    delete[] story_file_path;
    while (getline(myfile, line)) {
      bool declaration_check = is_page_declaration(line, argv[1]);
      std::cout << line + " is a " << declaration_check << " declaration page" << '\n';

      if (declaration_check) {
        // do stuff and add other bools once translated into code
      }

      else {
        // set all bools to false to error out
        //declaration_check = false;
        //line_failure = true;
        //zbreak;
      }
    }
  }
  myfile.close();
  if (line_failure) {
    std::cerr << "The line" + line +
                     " in story.txt did not follow the proper format for being a "
                     "declaration or choice page. In the case of the declaration, the "
                     "error may have also been the non-existance of the page file.\n";
    exit(EXIT_FAILURE);
  }

  std::cout << "Program compiles " << std::endl;

  return EXIT_SUCCESS;
}
