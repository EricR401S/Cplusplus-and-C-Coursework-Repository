#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
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
    return valid;
  }
  for (size_t i = 0; i < search_2.size(); i++) {
    found = some_str.find(search_2[i]);

    if (found != std::string::npos) {
      valid = true;
    }
  }

  return valid;
}

std::string get_size_t_max_value() {
  //Returns the max size_t on the system in string form

  size_t ceiling = -1;

  std::stringstream ss;

  ss << ceiling;

  return ss.str();
}

bool are_digits_until_position(std::string some_string, size_t start, size_t position) {
  // Returns true if every character excluding the position is a digit

  size_t digit_counter = 0;

  for (size_t i = start; i < position; i++) {
    if (!isdigit(some_string[i])) {
      return false;
    }
    digit_counter++;
  }

  // running a check to see if it fits in a size_t
  // by using the max value and number of digits in that value

  std::string max_ceiling = get_size_t_max_value();

  if (digit_counter > max_ceiling.size()) {
    std::cerr << "Cannot convert large number into size_t\n";
    return false;
  }

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

  // check digits

  size_t at_location = story_line.find("@");

  if (!are_digits_until_position(story_line, 0, at_location)) {
    return false;
  }

  size_t new_counter = at_location + 1;

  if (story_line.substr(new_counter, 1) != "N" &&
      story_line.substr(new_counter, 1) != "W" &&
      story_line.substr(new_counter, 1) != "L") {
    return false;
  }
  new_counter++;

  if (story_line.substr(new_counter, 1) != ":") {
    return false;
  }

  new_counter++;

  std::string filename = story_line.substr(new_counter);
  if (!directory_file_exists(dirname, filename)) {
    std::cerr << filename << " is not a valid filename\n";
    return false;
  }

  return true;
}

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
  }

  catch (const std::out_of_range & numtoolarge) {
    std::cerr << "Error in declaration line : number " << page_num << " is too large.\n";
    exit(EXIT_FAILURE);
  }

  std::size_t moving_counter = at_location + 1;

  std::string page_type = story_line.substr(moving_counter, 1);

  moving_counter += 2;

  std::string filename = story_line.substr(moving_counter);

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

  if (!are_digits_until_position(story_line, 0, colon_first_position) ||
      !are_digits_until_position(
          story_line, colon_first_position + 1, colon_second_position) ||
      cstr[colon_first_position + 1] == ':') {
    return false;
  }

  return true;
}

void parse_choice_line(std::string story_line, Story & a_story) {
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

  // add the choice

  a_story.add_choice(choice_text, page_num, destination_num);
}

bool is_whitespace_line(std::string line) {
  // Return true if whitespace is a line

  // the checks run below
  size_t line_sz = line.size();

  if (line_sz == 0) {
    // had only one newline when used with getline
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

std::pair<size_t, size_t> optimized_page_search(size_t page_number,
                                                size_t some_page_count) {
  // Returns the start and end ranges for loops
  // in an effort to reduce search time complexity

  size_t end_range = some_page_count;
  size_t start_range = 0;
  if (some_page_count > 10 && page_number >= some_page_count / 2) {
    start_range = some_page_count / 2;
  }

  else if (some_page_count > 10 && page_number < some_page_count / 2) {
    end_range = some_page_count / 2;
  }

  std::pair<size_t, size_t> result(start_range, end_range);

  return result;
}

size_t read_user_choice(std::vector<std::pair<std::string, size_t> > page_choices) {
  // Returns a number for referencing the page choice which the user desires
  // If the page is not a valid page choice, the user receives a message indicating that another option must be given.

  bool number_found = false;
  size_t choice;
  size_t options_count = page_choices.size();

  while (!number_found) {
    std::string user_input;

    std::cin >> user_input;

    if (is_whitespace_line(user_input)) {
      std::cout << "That is not a valid choice, please try again\n";
      continue;
    }

    try {
      choice = strtoul(user_input.c_str(), NULL, 10);
      if (choice >= 1 && choice <= options_count) {
        number_found = true;
      }
      else {
        std::cout << "That is not a valid choice, please try again\n";
      }
    }

    catch (...) {
      std::cout << "That is not a valid choice, please try again\n";
    }
    std::cin.clear();
  }
  return choice;
}

void choose_your_own_adventure(Story & the_story) {
  // Reads the user choices and navigates the story pages to reach
  // a win or lose page, which finishes the story and triggers a successful exit of the program

  bool game_finished = false;

  size_t page_to_show = 0;

  while (!game_finished) {
    Page * curr_page = the_story.get_page(page_to_show);

    the_story.update_map(page_to_show);
    std::set<size_t> available_choices = the_story.revise_available_choices(page_to_show);

    curr_page->print_page();

    if (curr_page->get_page_type() != "N") {
      game_finished = true;
      continue;
    }

    else {
      std::set<size_t>::iterator end_it = available_choices.end();
      bool valid = false;
      while (!valid) {
        size_t user_choice = read_user_choice(*(curr_page->get_choices()));
        std::set<size_t>::iterator it = available_choices.find(user_choice);
        if (it != end_it) {
          valid = true;
          page_to_show = (*(curr_page->get_choices()))[user_choice - 1].second;
        }
        else {
          std::cout << "That choice is not available at this time, please try again\n";
        }
      }
    }
  }
  return;
}

void print_winning_paths(
    std::vector<std::pair<std::vector<size_t>, std::set<size_t> > > & winning_paths,
    Story & the_story) {
  // Prints all the solution paths for the story that end with a win page,
  // where each page has a corresponding parentheses indicating the choice
  //necessary to reach the next page in the correct path.

  // for each path
  for (size_t i = 0; i < winning_paths.size(); i++) {
    size_t path_size = winning_paths[i].first.size();
    // for each page
    for (size_t j = 0; j < path_size; j++) {
      //
      Page * curr_page = the_story.get_page(winning_paths[i].first[j]);

      if (j != path_size - 1) {
        std::vector<std::pair<std::string, size_t> > choices =
            *(curr_page->get_choices());

        for (size_t k = 0; k < choices.size(); k++) {
          if (choices[k].second == winning_paths[i].first[j + 1]) {
            std::cout << winning_paths[i].first[j] << "(" << k + 1 << "),";
          }
        }
      }
      else {
        std::cout << winning_paths[i].first[j] << "(win)\n";
      }
    }
  }
}

void funnel_win_paths(
    std::vector<std::pair<std::vector<size_t>, std::set<size_t> > > & path_queue,
    std::vector<std::pair<std::vector<size_t>, std::set<size_t> > > & winning_paths,
    Story & the_story) {
  // Remove the paths that ended in terminal pages (win/loss) and send the winning paths to the container called win_paths

  std::vector<size_t> path_removal_list;

  for (size_t i = 0; i < path_queue.size(); i++) {
    size_t ith_path_sz = path_queue[i].first.size();

    size_t last_page_n_in_path = path_queue[i].first[ith_path_sz - 1];

    // last page is exploration departure point
    Page * last_page_in_path = the_story.get_page(last_page_n_in_path);

    std::string curr_page_type = last_page_in_path->get_page_type();

    if (curr_page_type == "L") {
      path_removal_list.push_back(i);
    }

    else if (curr_page_type == "W") {
      std::set<size_t> win_set__copy(path_queue[i].second);
      std::vector<size_t> win_path_vector(path_queue[i].first);
      std::pair<std::vector<size_t>, std::set<size_t> > win_path;
      win_path.first = win_path_vector;
      win_path.second = win_set__copy;
      winning_paths.push_back(win_path);
      path_removal_list.push_back(i);
    }

    else {
      continue;
    }
  }

  for (size_t j = 0; j < path_removal_list.size(); j++) {
    path_queue.erase(path_queue.begin() + (path_removal_list[j] - j));
  }
}

void find_next_paths(
    std::vector<std::pair<std::vector<size_t>, std::set<size_t> > > & path_queue,
    Story & the_story) {
  // Produces the next paths based on Breadth First Search and cleans the old queue in order to add the new paths.

  // These are the indices to remove from the path queues
  // because we don't want to infinitely repeat searches,
  // so we record the indices of all the old paths to remove
  // if there were 3 paths in queue, and they expand to 12 possible paths,
  // remove paths in the indices 0 through 2.
  // This is the purpose of updated_paths_to_remove;
  size_t updated_path_to_remove = path_queue.size();

  for (size_t i = 0; i < updated_path_to_remove; i++) {
    // for path in the queue, as it was received

    size_t ith_path_sz = path_queue[i].first.size();

    size_t last_page_n_in_path = path_queue[i].first[ith_path_sz - 1];

    // last page is exploration departure point
    Page * last_page_in_path = the_story.get_page(last_page_n_in_path);

    assert(last_page_in_path->get_page_type() == "N" &&
           "This page must be a Normal Choice Page");

    std::vector<std::pair<std::string, size_t> > page_choices =
        *(last_page_in_path->get_choices());

    // commence exploring the node
    for (size_t j = 0; j < page_choices.size(); j++) {
      size_t next_page_destination = page_choices[j].second;

      std::set<size_t> new_set_to_copy(path_queue[i].second);

      std::pair<std::set<size_t>::iterator, bool> ret =
          new_set_to_copy.insert(next_page_destination);

      if (ret.second == false) {
        // no repeated nodes
        continue;
      }

      else {
        std::vector<size_t> new_path_vector(path_queue[i].first);
        new_path_vector.push_back(next_page_destination);
        std::pair<std::vector<size_t>, std::set<size_t> > new_path;
        new_path.first = new_path_vector;
        new_path.second = new_set_to_copy;
        path_queue.push_back(new_path);
      }
    }
  }
  path_queue.erase(path_queue.begin(), path_queue.begin() + updated_path_to_remove);
}

void find_winning_paths(Story & the_story) {
  // Finds and Prints all cycle free paths to win a cyoa story

  size_t start_page = 0;

  // Within the pairs, the vector is the path being traversed, and the
  // set is the corresponding set to that path, as a means of avoiding duplicates
  std::vector<std::pair<std::vector<size_t>, std::set<size_t> > > path_queue;

  std::vector<std::pair<std::vector<size_t>, std::set<size_t> > > winning_paths;

  // preparing the first page vector

  std::pair<std::vector<size_t>, std::set<size_t> > start;

  start.first = std::vector<size_t>(1, start_page);

  start.second = std::set<size_t>();

  start.second.insert(start_page);

  path_queue.push_back(start);

  int count = 0;

  while (path_queue.size() != 0) {
    find_next_paths(path_queue, the_story);

    funnel_win_paths(path_queue, winning_paths, the_story);

    count++;
  }

  if (winning_paths.size() == 0) {
    std::cout << "This story is unwinnable!\n";
    return;
  }

  // print winning paths

  print_winning_paths(winning_paths, the_story);
};

bool digit_checker_long_int(std::string some_line, size_t equal_start, size_t end) {
  // Returns true if the string sequence within the range is a valid long int
  // the start refers to the equal sign

  size_t sz = end;  // can be size of the line

  // to handle a case like 4$pastry=2,
  // one positive number after the equal sign
  if (sz - equal_start - 1 == 1) {
    if (isdigit(some_line.c_str()[sz - 1])) {
      return true;
    }
    else {
      return false;
    }
  }
  else if (sz - equal_start - 1 >= 2) {
    // for all the other cases like 4$pastry=-5 or 5$jump=128
    // track if the first character after
    // equal sign is a minus sign

    const char * line_cstr = some_line.c_str();

    if (isdigit(line_cstr[equal_start + 1]) || line_cstr[equal_start + 1] == '-') {
      // this is ok, while the converse is not
    }

    else {
      return false;
    }

    //moving on to all of the digits after the first - sign or digit
    for (size_t i = equal_start + 2; i < sz; i++) {
      if (!isdigit(line_cstr[i])) {
        return false;
      }
    }
  }

  return true;
}

size_t backwards_location_char_finder(std::string story_line, const char char_to_find) {
  // Returns the position of the last ocurrence of the character

  size_t line_sz = story_line.size();

  const char * line_cstr = story_line.c_str();

  for (size_t i = line_sz - 1; i >= 0; i--) {
    if (line_cstr[i] == char_to_find) {
      return i;
    }
  }
  // 0 means not found
  return 0;
}

bool variable_check(std::string story_line) {
  // Returns true if the string indicates a variable to record
  // a user choice, false otherwise

  if (!is_found(story_line, '$') || !is_found(story_line, '=')) {
    return false;
  }

  size_t $_location = story_line.find('$');
  size_t equal_location = backwards_location_char_finder(story_line, '=');
  size_t sz = story_line.size();

  if ($_location == 0 || equal_location == (sz - 1)) {
    // can't start the line with $
    return false;
  }

  else {
    if (!are_digits_until_position(story_line, 0, $_location) ||
        !digit_checker_long_int(story_line, equal_location, sz)) {
      return false;
    }
  }

  // For the variable declarations with
  // no variable names
  if ((equal_location - $_location) == 1) {
    return false;
  }

  return true;
}

std::pair<size_t, std::pair<std::string, long int> > variable_parser(
    std::string story_line) {
  // Returns a pair consisting of the page number
  // and a pair of variable name and the value as a long integer
  // for use in the story's internal maps
  size_t $_location = story_line.find('$');
  size_t equal_location = backwards_location_char_finder(story_line, '=');

  // substrings for conversions : page number
  std::string page_number_string = story_line.substr(0, $_location);

  size_t page_number = strtoul(page_number_string.c_str(), NULL, 10);

  // variable name and value

  std::string variable_name =
      story_line.substr($_location + 1, equal_location - $_location - 1);

  std::string var_value_str = story_line.substr(equal_location + 1);

  long int var_value = strtol(var_value_str.c_str(), NULL, 10);

  std::pair<std::string, long int> var_val_pair;

  var_val_pair.first = variable_name;

  var_val_pair.second = var_value;

  std::pair<size_t, std::pair<std::string, long int> > page_kv_pair;
  page_kv_pair.first = page_number;
  page_kv_pair.second = var_val_pair;

  return page_kv_pair;
}

bool conditional_choice_checker(std::string story_line) {
  // Returns true if the line is a conditional choice
  // the assumption made is that the brackets will always
  // enclose the variable name and value
  if (!is_found(story_line, '[') || !is_found(story_line, ']') ||
      !is_found(story_line, '=')) {
    return false;
  }

  size_t location_left_bracket = story_line.find("[");

  size_t location_right_bracket = story_line.find("]");

  if (location_left_bracket == 0 || location_right_bracket == 0 ||
      (location_left_bracket > location_right_bracket) ||
      story_line.c_str()[location_right_bracket + 1] != ':') {
    return false;
  }

  // Split the string into the original choice and
  // condition with the variable name and value

  std::string choice_string = story_line.substr(0, location_left_bracket) +
                              story_line.substr(location_right_bracket + 1);

  std::string variable_string = story_line.substr(
      location_left_bracket + 1, location_right_bracket - location_left_bracket - 1);

  size_t equal_location = backwards_location_char_finder(variable_string, '=');

  if (equal_location == variable_string.size() - 1 || equal_location == 0) {
    return false;
  }

  if (!digit_checker_long_int(variable_string, equal_location, variable_string.size())) {
    return false;
  }

  if (is_found(variable_string, '[') || is_found(variable_string, ']') ||
      is_found(variable_string, ':')) {
    return false;
  }

  // the split was to repurpose the choice parsing function
  if (!is_choice_page(choice_string)) {
    return false;
  }

  return true;
}
std::pair<std::string, std::pair<size_t, std::pair<std::string, long int> > >
conditional_choice_parser(std::string story_line) {
  // Returns a pair consisting of a choice string and a secondary pair.
  // The secondary pair constains the page number and
  // the condition for the choice stored as another pair
  // (choice string, (page number , (variable name, value ) ) )
  size_t location_left_bracket = story_line.find("[");

  size_t location_right_bracket = story_line.find("]");

  // Split the string into the original choice and
  // condition with the variable name and value

  std::string choice_string = story_line.substr(0, location_left_bracket) +
                              story_line.substr(location_right_bracket + 1);

  std::string variable_string = story_line.substr(
      location_left_bracket + 1, location_right_bracket - location_left_bracket - 1);

  size_t equal_location = backwards_location_char_finder(variable_string, '=');

  std::string var_name = variable_string.substr(0, equal_location);

  std::string var_num_str = variable_string.substr(equal_location + 1);

  long int var_number = strtol(var_num_str.c_str(), NULL, 10);

  std::string page_number_string = story_line.substr(0, location_left_bracket);

  size_t page_number = strtoul(page_number_string.c_str(), NULL, 10);

  std::pair<std::string, std::pair<size_t, std::pair<std::string, long int> > > result;

  result.first = choice_string;

  result.second.first = page_number;

  result.second.second.first = var_name;

  result.second.second.second = var_number;

  return result;
}
