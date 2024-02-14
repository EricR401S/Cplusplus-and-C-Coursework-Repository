#ifndef __T_STORY_H___
#define __T_STORY_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// Functions immediately necessary for story class methods

std::pair<size_t, size_t> optimized_page_search(size_t page_number,
                                                size_t some_page_count);

// Page classes to manipulate the types of story pages

class Page {
  // This class stores the contents
  // and page of a story page
  // It is the base for all the
  // other pages
 protected:
  size_t page_num;

  std::string text;

 public:
  // The default constructor will take uncommon, but arbitrary values
  // 9999 is preferable in the case that a page number is actually 0
  Page() : page_num(9999), text("") {}

  // The arguments are POD
  Page(size_t number, std::string contents) : page_num(number), text(contents) {}

  // copy_constructor is POD
  Page(const Page & rhs) : page_num(rhs.page_num), text(rhs.text) {}

  // the destructor will vary across the children
  virtual ~Page() {}

  size_t get_page_num() const {
    //returns page number
    return page_num;
  }

  virtual std::string get_page_type() {
    // returns type of page, to be defined by children
    return "Base Page";
  }  // facilitates choice addition

  virtual Page * deep_copy() {
    // creates a deep copy of the page
    Page * copy_to_return = new Page(page_num, text);

    return copy_to_return;
  }

  // the print page will vary across children types
  virtual void print_page() { std::cout << text; }

  virtual void add_choice_option(size_t page_number,
                                 size_t page_destination,
                                 std::string choice_text) {
    // necessary placeholder function for choice page
    // adds choice to page
    return;
  }

  virtual void add_condition_option(std::pair<std::string, long int> kv_pair) {
    // necessary placeholder function for choice page
    // adds condition to page
    return;
  }

  virtual std::vector<std::pair<std::string, size_t> > * get_choices() {
    // Placeholder function for choice page to get choices
    std::vector<std::pair<std::string, size_t> > choices;
    std::vector<std::pair<std::string, size_t> > * ptr = &choices;
    return ptr;
  }

  virtual std::vector<std::pair<size_t, std::pair<std::string, long int> > > *
  get_conditions() {
    // Placeholder function for choice page to get conditions
    std::vector<std::pair<size_t, std::pair<std::string, long int> > > choices;
    std::vector<std::pair<size_t, std::pair<std::string, long int> > > * ptr = &choices;
    return ptr;
  }
};

class ChoicePage : public Page {
  // A ChoicePage has the typical page behavior, but adds the ability
  // to store choices and print the text in an appropriate way
  std::vector<std::pair<std::string, size_t> > choices;

  std::vector<std::pair<size_t, std::pair<std::string, long int> > > conditional_choices;

  size_t choice_num;

 public:
  ChoicePage() : Page(), choice_num(0){};

  ChoicePage(std::string page_body, size_t page_num) :
      Page(page_num, page_body), choice_num(0) {}

  ChoicePage(const ChoicePage & rhs) : choice_num(rhs.choice_num) {
    // copy constructor
    text = rhs.text;
    page_num = rhs.page_num;
    choices.resize(rhs.choices.size());
    for (size_t i = 0; i < choice_num; i++) {
      choices[i] = rhs.choices[i];
    }

    conditional_choices.resize(rhs.conditional_choices.size());
    for (size_t j = 0; j < rhs.conditional_choices.size(); j++) {
      conditional_choices[j].first = rhs.conditional_choices[j].first;
      conditional_choices[j].second.first = rhs.conditional_choices[j].second.first;
      conditional_choices[j].second.second = rhs.conditional_choices[j].second.second;
    }
  }

  virtual ~ChoicePage() {}
  //destructor, the data structures used have their own destructors

  virtual std::string get_page_type() { return "N"; }  // facilitates choice addition

  virtual std::vector<std::pair<std::string, size_t> > * get_choices() {
    // Returns a pointer to the choice vector

    std::vector<std::pair<std::string, size_t> > * ptr = &choices;
    return ptr;
  }

  virtual std::vector<std::pair<size_t, std::pair<std::string, long int> > > *
  get_conditions() {
    // Returns a pointer to the conditions vector
    std::vector<std::pair<size_t, std::pair<std::string, long int> > > * ptr =
        &conditional_choices;
    return ptr;
  }

  virtual void add_choice_option(size_t page_number,
                                 size_t page_destination,
                                 std::string choice_text) {
    // Adds the choice + destination to the choices vector
    assert((page_num == page_number) &&
           "This is not the right page for choice insertion");

    std::pair<std::string, size_t> choice_with_destination;

    choice_with_destination.first = choice_text;
    choice_with_destination.second = page_destination;
    choices.push_back(choice_with_destination);
    choice_num++;
  }

  virtual void add_condition_option(std::pair<std::string, long int> kv_pair) {
    // Adds the condition to the conditional vector.
    // This assumes the choice was added first.
    std::pair<size_t, std::pair<std::string, long int> > condition;
    condition.first = choices.size() - 1;
    condition.second = kv_pair;
    conditional_choices.push_back(condition);
    return;
  }

  virtual Page * deep_copy() {
    // returns deep copy of the choice page
    ChoicePage * copy_to_return = new ChoicePage(text, page_num);
    copy_to_return->choices.resize(choices.size());
    copy_to_return->conditional_choices.resize(conditional_choices.size());
    //copy_to_return->choices = choices;
    copy_to_return->choice_num = choice_num;
    for (size_t i = 0; i < choice_num; i++) {
      copy_to_return->choices[i] = choices[i];  // check
    }
    for (size_t j = 0; j < conditional_choices.size(); j++) {
      copy_to_return->conditional_choices[j] = conditional_choices[j];  // check
    }
    return copy_to_return;
  }

  virtual void print_page() {
    // Prints the contents of the page according to the README
    std::cout << text << "\n"
              << "What would you like to do?\n";

    assert(choice_num == choices.size() && "Your choice num is wrong\n");
    for (size_t i = 0; i < choice_num; i++) {
      std::cout << "\n"
                << " " << i + 1 << ". " << choices[i].first;
    }
    std::cout << std::endl;
  }
};

class TerminalPage : public Page {
  // This is the version of the page that ends the story

  bool win_lose_flag;  // this determines the final message

 public:
  TerminalPage() : Page(), win_lose_flag(false){};

  TerminalPage(std::string page_body, size_t page_num, bool is_win) :
      Page(page_num, page_body), win_lose_flag(is_win) {}

  TerminalPage(const TerminalPage & rhs) : win_lose_flag(rhs.win_lose_flag) {
    // copy constructor
    text = rhs.text;
    page_num = rhs.page_num;
  }

  virtual ~TerminalPage() {}
  //destructor, the data structures used have their own destructors

  virtual Page * deep_copy() {
    TerminalPage * copy_to_return = new TerminalPage(text, page_num, win_lose_flag);
    return copy_to_return;
  }

  virtual std::string get_page_type() {
    // Returns identifying letter for win or lose page
    if (win_lose_flag) {
      return "W";
    }
    else {
      return "L";
    }
  }

  virtual void print_page() {
    // Prints the contents of the page according to the README

    std::cout << text << "\n";

    if (win_lose_flag) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
      ;
    }

    else {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }

    return;
  }
};

class Story {
  // This is a story class
  // that stores the story pages

 protected:
  std::vector<Page *> story_pages;
  size_t page_count;
  // tracks the highest page number of the destination pages referenced by the choices
  size_t max_destination;
  bool have_win_page;
  bool have_lose_page;

  // a set for determining if the pages other than 0 have a backreference

  std::set<size_t> backreference_set;

  // two maps, one to hold all the keys and their current value states i.e. sword = 0
  // and one to hold all the page specific variable changes, i.e. page 7 has 3 variables that undergo value changes
  // one set to hold all the pages that trigger value changes i.e. a set of pages 3,7,9 that should trigger value changes for the keys
  std::map<std::string, long int> current_state_variable_map;
  std::map<size_t, std::vector<std::pair<std::string, long int> > >
      variable_change_map_by_page;
  std::set<size_t> var_change_pages_set;

 public:
  Story() :
      page_count(0),
      max_destination(0),
      have_win_page(false),
      have_lose_page(
          false){};  // only a default constructor is necessary, as no arguments will be taken

  Story(const Story & rhs) {
    // Takes in rhs to copy construct a Story object
    page_count = rhs.get_page_count();

    story_pages.resize(page_count);

    max_destination = rhs.max_destination;

    have_win_page = rhs.have_win_page;

    have_lose_page = rhs.have_lose_page;

    for (size_t i = 0; i < rhs.get_page_count(); i++) {
      story_pages[i] = rhs.story_pages[i]->deep_copy();
    }

    backreference_set = rhs.backreference_set;
    current_state_variable_map = rhs.current_state_variable_map;
    variable_change_map_by_page = rhs.variable_change_map_by_page;
    var_change_pages_set = rhs.var_change_pages_set;
  }

  ~Story() {
    // Free all the memory allocated for every single page

    for (size_t i = 0; i < page_count; i++) {
      delete story_pages[i];
    }
  };

  size_t get_page_count() const { return page_count; }  // returns page count

  // returns highest page number designated as a destination by a choice
  size_t get_max_destination_value() const { return max_destination; }

  bool page_exists(size_t page_number) {
    // Returns true if page exists
    for (size_t i = 0; i < page_count; i++) {
      if (story_pages[i]->get_page_num() == page_number) {
        return true;
      }
    }
    return false;
  }

  bool page_exists_range(size_t page_number) {
    // Returns true if page exists within certain range

    std::pair<size_t, size_t> ranges = optimized_page_search(page_number, page_count);

    size_t start_range = ranges.first;
    size_t end_range = ranges.second;

    for (size_t i = start_range; i < end_range; i++) {
      //

      if (story_pages[i]->get_page_num() == page_number) {
        return true;
      }
    }
    return false;
  }

  Page * get_page(size_t page_number) const {
    // Retrieves a pointer to the page of interest

    std::pair<size_t, size_t> ranges = optimized_page_search(page_number, page_count);

    size_t start_range = ranges.first;
    size_t end_range = ranges.second;

    Page * page_pointer = NULL;

    for (size_t i = start_range; i < end_range; i++) {
      if (story_pages[i]->get_page_num() == page_number) {
        page_pointer = story_pages[i];
      }
    }
    return page_pointer;
  }

  void add_page(Page * some_page) {
    // Adds page to the story
    // Prior page to page of interest must exist
    // unless the page to add is 0
    // i.e. 12 can only be added if 11 exists

    if (page_count == 0) {
      if (some_page->get_page_num() != 0) {
        std::cerr << "User Error : First page must be page 0\n";
        exit(EXIT_FAILURE);
      }
      page_count = page_count + 1;
      story_pages.resize(page_count);
      story_pages[page_count - 1] = some_page;
    }

    else if (page_exists_range(some_page->get_page_num())) {
      std::cerr << "User Error : Page -" << some_page->get_page_num()
                << "- already exists\n";
      exit(EXIT_FAILURE);
    }

    else {
      if (page_exists_range(some_page->get_page_num() - 1)) {
        page_count++;
        story_pages.resize(page_count);
        story_pages[page_count - 1] = some_page;
        if (some_page->get_page_type() == "W") {
          have_win_page = true;  // update the bools
        }
        else if (some_page->get_page_type() == "L") {
          have_lose_page = true;  // necessary for win_lose_checker
        }
      }

      else {
        std::cerr << "User Error : You are not adding the pages consecutively\n";
        exit(EXIT_FAILURE);
      }
    }
  }

  void add_choice(std::string choice_text, size_t page_number, size_t destination) {
    // Adds a choice to the given page if it exists

    bool found = false;
    for (size_t i = 0; i < page_count; i++) {
      if (story_pages[i]->get_page_num() == page_number) {
        if (story_pages[i]->get_page_type() != "N") {
          std::cerr << "Page is not a NORMAL/CHOICE page\n";
          exit(EXIT_FAILURE);
        }
        story_pages[i]->add_choice_option(page_number, destination, choice_text);
        found = true;
        // to check for invalid forward references in check_destination method
        if (destination > max_destination) {
          max_destination = destination;
        }
        if (destination != 0) {                   // avoid adding zero as an entry
          backreference_set.insert(destination);  // for check_backreferences method
        }
      }
    }

    if (!found) {
      std::cerr << "Requested page-" << page_number << "-not found.\n";
      exit(EXIT_FAILURE);
    }
  }

  void add_condition(size_t page_number, std::pair<std::string, long> kv_pair) {
    // Adds a condition to the last added choice, used in conjunction with add_choice
    // The condition is a key value pair holding the
    // destination of the choice to change and the variable-value pair
    // to search within the current mapo the given page if it exists

    Page * target_page = get_page(page_number);
    if (target_page->get_page_type() != "N") {
      std::cerr << "Page is not a NORMAL/CHOICE page\n";
      exit(EXIT_FAILURE);
    }
    target_page->add_condition_option(kv_pair);
  }

  std::set<size_t> revise_available_choices(size_t page_number) {
    // Change choices whose conditions do not match
    // the current state of the map to <UNAVAILABLE>
    // and return the set of available choices

    Page * current_page = get_page(page_number);

    std::set<size_t> correct_choices;

    if (current_page->get_page_type() != "N") {
    }

    else {
      std::vector<std::pair<std::string, size_t> > * choice_location =
          current_page->get_choices();

      for (size_t j = 0; j < (*choice_location).size(); j++) {
        correct_choices.insert((j + 1));
      }

      std::vector<std::pair<size_t, std::pair<std::string, long int> > > conditions =
          *(current_page->get_conditions());

      for (size_t i = 0; i < conditions.size(); i++) {
        std::map<std::string, long int>::iterator it =
            current_state_variable_map.find(conditions[i].second.first);

        bool no_change = true;

        if (it != current_state_variable_map.end()) {
          if (it->second != conditions[i].second.second) {
            no_change = false;
          }
        }
        if (!no_change) {
          ((*choice_location)[conditions[i].first]).first = "<UNAVAILABLE>";
          correct_choices.erase(conditions[i].first + 1);
        }
      }
    }

    return correct_choices;
  }

  void check_destinations() {
    // Exits with failure if the destination pages referenced do not exist
    if (max_destination >= page_count) {
      std::cerr << "User Error : There are pages referenced forwardly in the choices "
                   "that do not "
                   "exist. An example is page-"
                << max_destination << "-.\n";
      exit(EXIT_FAILURE);
    }
  }

  void check_win_lose_minimum() {
    // Exits with failure if at least not one W and L page is not found
    if (!(have_lose_page && have_win_page)) {
      std::cerr << "The story needs a minimum of one WIN page and one LOSE page\n";
      exit(EXIT_FAILURE);
    }
  }

  void check_backreferences() {
    // Exits with failure if the backreference set size is not equal to the (page count - 1)
    // because 0 does not need to be backreferenced

    if (backreference_set.size() != (page_count - 1)) {
      std::cerr << "Not all of the pages beyond page 0 are referenced by other choices\n";
      exit(EXIT_FAILURE);
    }
  }

  void add_key_to_aux_map(
      std::pair<size_t, std::pair<std::string, long int> > page_kv_pair) {
    // Add the key-value pair to the vector of KV pairs associated with the page;
    std::map<size_t, std::vector<std::pair<std::string, long int> > >::iterator it;

    it = variable_change_map_by_page.find(page_kv_pair.first);
    if (it == variable_change_map_by_page.end()) {
      // insert the new KV pair
      std::vector<std::pair<std::string, long int> > kv_vector;
      kv_vector.push_back(page_kv_pair.second);
      std::pair<size_t, std::vector<std::pair<std::string, long int> > > new_entry;
      new_entry.first = page_kv_pair.first;
      new_entry.second = kv_vector;
      variable_change_map_by_page.insert(new_entry);
    }

    else {
      it->second.push_back(page_kv_pair.second);
    }
  }

  void add_conditional_key(std::pair<std::string, long int> kv_pair) {
    // Adds keys found in conditional choices to current map
    // This method is geared mostly to handle keys that
    // have only been seen in conditional choices
    std::pair<std::string, long int> kv_pair_with_val_0;
    kv_pair_with_val_0.first = kv_pair.first;
    kv_pair_with_val_0.second = 0;
    current_state_variable_map.insert(kv_pair_with_val_0);
    return;
  }

  void add_key_to_map(std::pair<size_t, std::pair<std::string, long int> > page_kv_pair) {
    // Adds variable and value pair to:
    //a set of pages that need to trigger variable changes
    // a current map that holds the current state of the variable values
    // as the story is traversed
    // and a map of the pages with vectors of the variables that need their values to be changed

    if (!page_exists_range(page_kv_pair.first)) {
      std::cerr << "User Error : Page " << page_kv_pair.first
                << " does not exist for variable declaration\n";
      exit(EXIT_FAILURE);
    }

    var_change_pages_set.insert(page_kv_pair.first);

    current_state_variable_map.insert(
        std::pair<std::string, long int>(page_kv_pair.second.first, 0));

    // Add the key to the auxiliary map
    add_key_to_aux_map(page_kv_pair);
  }

  void update_map(size_t current_page) {
    // Update the current map's values depending if the page
    // requires a value change from a variable

    std::set<size_t>::iterator it = var_change_pages_set.find(current_page);

    if (it != var_change_pages_set.end()) {
      // update the variables in the current map present
      // in the vector associated with the page

      std::vector<std::pair<std::string, long int> > page_vector =
          variable_change_map_by_page.find(current_page)->second;

      for (size_t i = 0; i < page_vector.size(); i++) {
        current_state_variable_map.find(page_vector[i].first)->second =
            page_vector[i].second;
      }
    }
  }

  bool is_value_for_key(std::pair<std::string, long int> kv) {
    // Returns true if the value associated with the key
    // is the same as the kv.second, else false

    std::map<std::string, long int>::iterator it =
        current_state_variable_map.find(kv.first);

    if (it != current_state_variable_map.end()) {
      // update the variables in the current map present
      // in the vector associated with the page

      if (it->second == kv.second) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }

  void print_story() {
    // Prints all the story pages using their respective printing methods
    for (size_t i = 0; i < page_count; i++) {
      // print page number first, then contents
      std::cout << "Page " << story_pages[i]->get_page_num() << "\n"
                << "==========\n";

      story_pages[i]->print_page();
    }
  }
};

// Functions necessary for story parsing and other story needs

std::string combine_dir_file_names(char * dir_name, std::string name_of_file);

int directory_file_exists(char * some_arg, std::string name_of_file);

char * file_charname(char * dir_name, std::string name_of_file);
std::string file_to_string(char * dir_name, std::string name_of_file);
bool is_declaration_requirment_met(std::string some_str);
bool is_page_declaration(std::string story_line, char * dirname);

void parse_declaration(std::string story_line, char * dirname);
Page * parse_declaration_page(std::string story_line, char * dirname);
bool is_choice_page(std::string story_line);

void parse_choice_line(std::string story_line, Story & a_story);

bool is_whitespace_line(std::string line);

size_t read_user_choice(std::vector<std::pair<std::string, size_t> > page_choices);

void choose_your_own_adventure(Story & the_story);

void find_winning_paths(Story & the_story);

bool variable_check(std::string story_line);

std::pair<size_t, std::pair<std::string, long int> > variable_parser(
    std::string story_line);

bool conditional_choice_checker(std::string story_line);

std::pair<std::string, std::pair<size_t, std::pair<std::string, long int> > >
conditional_choice_parser(std::string story_line);

#endif
