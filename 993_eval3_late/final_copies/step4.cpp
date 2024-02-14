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
      bool declaration_check = is_page_declaration(line, argv[1]);
      bool choice_check = is_choice_page(line);
      bool whitespace_check = is_whitespace_line(line);
      //bool var_check = variable_check(line);
      bool var_spread_check = variable_pseudo_check(line);
      bool conditional_choice_check = conditional_choice_checker(line);
      if (declaration_check) {
        // do stuff and add other bools once translated into code
        //std::cout << line + " is a " << declaration_check << " declaration page" << '\n';
        //parse_declaration(line, argv[1]);
        Page * my_page = parse_declaration_page(line, argv[1]);
        my_story.add_page(my_page);
        //my_page->print_page();
        //delete my_page;
        continue;
      }

      else if (choice_check) {
        //        std::cout << line + " is a " << choice_check << " choice page" << '\n';
        //parse_choice_line(line);
        parse_choice_line(line, my_story);
      }

      else if (whitespace_check) {
        // std::cout << " The line-" << line << "- is just empty\n";
        continue;
      }

      // else if (var_check) {
      //   std::cout << " The line-" << line << "- is a " << var_check
      //             << " variable declaration line\n";
      //   std::pair<std::string, long int> var_val_res = variable_parser(line);
      //   std::cout << "The variable name	is -" << var_val_res.first
      //             << "- and the variable value is -" << var_val_res.second << "-\n";
      //   continue;
      // }

      else if (var_spread_check) {
        // std::cout << " The line-" << line << "- is a " << var_spread_check
        //           << " variable spread declaration line\n";

        std::pair<size_t, std::pair<std::string, long int> > var_val_res =
            variable_parser(line);
        // std::cout << "The page number is -" << var_val_res.first
        //           << "-. The variable name is -" << var_val_res.second.first
        //           << "- and the variable value is -" << var_val_res.second.second
        //           << "-\n";
        my_story.add_key_to_map(var_val_res);
        continue;
      }

      else if (conditional_choice_check) {
        //std::cout << " The line-" << line << "- is a conditional choice\n";
        std::pair<std::string, std::pair<size_t, std::pair<std::string, long int> > >
            choice_with_condition;  // the pair(choice string, pair(page number, pair(condition variable name, long int)))
        choice_with_condition = conditional_choice_parser(line);

        // std::cout << "The parsed choice is -" << choice_with_condition.first
        //           << "- and the page number is -" << choice_with_condition.second.first
        //           << "- and the variable is -"
        //           << choice_with_condition.second.second.first
        //           << "- and the var number is -"
        //           << choice_with_condition.second.second.second << "-\n";
        parse_choice_line(choice_with_condition.first, my_story);
        my_story.add_conditional_key(choice_with_condition.second.second);
        my_story.add_condition(choice_with_condition.second.first,
                               choice_with_condition.second.second);
        continue;
      }

      else {
        //  std::cout
        // << "The line-" << line
        // << "-is not a declaration or a choice page or a variable declaration.\n";
        //set all bools to false to error out
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
                     "declaration or choice page or a variable declaration. In the case "
                     "of the declaration, the "
                     "error may have also been the non-existance of the page file.\n";
    exit(EXIT_FAILURE);
  }

  //print the story
  //step 1 finale below
  //my_story.print_story();

  //step 2 checks beginning
  //my_story.check_destinations();
  //my_story.check_win_lose_minimum();
  //my_story.check_backreferences();

  //=============================================================
  // std::cout << "\nMy story's maximum destination number is "
  //           << my_story.get_max_destination_value() << "\n";
  // std::cout << "\nTesting getting page mechanisms. Looking for page 5"
  //           << "\n\n";

  // Page * calling_five = my_story.get_page(5);
  // calling_five->print_page();
  // std::cout << "\nTesting getting choices. Looking for page 5"
  //           << "\n\n";

  // std::vector<std::pair<std::string, size_t> > choices_for_five =
  //     *(calling_five->get_choices());

  // for (size_t i = 0; i < choices_for_five.size(); i++) {
  //   std::cout << "My choice text is -" << choices_for_five[i].first
  //             << "-  and my choice destination is -" << choices_for_five[i].second
  //             << "-\n";
  // }

  // std::cout << "\n";

  // std::cout << "I am testing the read user input\n";

  // size_t my_choice = read_user_choice(choices_for_five);

  // std::cout << "My choice for this page is choice number -" << my_choice
  //           << "- which leads to :\n"
  //           << choices_for_five[my_choice - 1].first << "-, where it will lead to page-"
  //           << choices_for_five[my_choice - 1].second << "-.\n";

  // std::cout << "Program compiles for step2" << std::endl;

  // std::cout << "Beginning step 2 test for the user choices with new function\n\n\n\n\n";

  //choose_your_own_adventure(my_story);

  // std::pair<size_t, std::pair<std::string, long int> > nv = variable_parser("7$SHADOW=5");
  // my_story.add_key_to_map(nv);
  // my_story.add_conditional_key(nv.second);
  // my_story.update_map(7);
  // my_story.add_key_to_map(nv);

  //std::cout
  //  << "\n\n\nStarting to choose my own adventure now :::: Running checks first\n\n";

  //step 2 checks beginning
  my_story.check_destinations();
  my_story.check_win_lose_minimum();
  my_story.check_backreferences();

  //std::cout << "Begin  Adventure \n\n\n";

  choose_your_own_adventure(my_story);
  return EXIT_SUCCESS;
}
