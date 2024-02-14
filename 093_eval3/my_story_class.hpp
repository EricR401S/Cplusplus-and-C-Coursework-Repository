#ifndef __T_STORY_H___
#define __T_STORY_H___

#include <assert.h>
//#include <stdlib.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Page {
  // This class stores the contents
  // and page of a story page
  // It is the base for all the
  // other pages
  // protected:
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

  //public:
  virtual ~Page() {}

  size_t get_page_num() const {
    //returns page number
    return page_num;
  }

  virtual std::string get_page_type() {
    return "Base Page";
  }  // facilitates choice addition

  virtual Page * deep_copy() {  // was virtual
                                // Page * deep_copy() {        // was virtual

    Page * copy_to_return = new Page(page_num, text);

    return copy_to_return;
  }

  // virtual Page * deep_copy() const = 0;

  //virtual void print_page() const = 0;
  // the print page will vary across children types
  virtual void print_page() {
    // prints the contents of the page according to the README
    // Page number first, then contents.

    std::cout << "Page " << page_num << "\n"
              << "==========\n"
              << text;
  }

  virtual void add_choice_option(size_t page_number,
                                 size_t page_destination,
                                 std::string choice_text) {
    std::cout << "Hey Eric, the choice code is using the page virtual method, MAYDAY!!!!"
              << std::endl;
    //std::cout << page_number << page_destination << choice_text;
    return;
  }

  // virtual void add_choice_option(size_t page_number,
  //                                size_t page_destination,
  //                                std::string choice_text) const = 0;
  // ;
};

class ChoicePage : public Page {
  // A ChoicePage has the typical page behavior, but adds the ability
  // to store choices and print the text in an appropriate way

  //still private fields

  //std::vector<size_t> destina

  //private:
  //protected:
  std::vector<std::pair<std::string, size_t> > choices;

  size_t choice_num;

 public:
  ChoicePage() : Page(), choice_num(0){};

  // ChoicePage(std::string page_body,
  //            size_t page_num,
  //            size_t page_destination,
  //            std::string choice_text) :
  //     Page(page_num, page_body) {
  //   std::pair<std::string, size_t> choice_with_destination;

  //   choice_with_destination.first = choice_text;

  //   choice_with_destination.second = page_destination;

  //   choices.push_back(choice_with_destination);

  //   choice_num++;
  // }

  ChoicePage(std::string page_body, size_t page_num) :
      Page(page_num, page_body), choice_num(0) {}

  ChoicePage(const ChoicePage & rhs) :
      //Page(rhs.text, rhs.page_num),
      // text(rhs.text),
      // page_num(rhs.page_num),
      //choices(rhs.choices),
      choice_num(rhs.choice_num) {
    //
    text = rhs.text;
    page_num = rhs.page_num;
    choices.resize(rhs.choices.size());
    for (size_t i = 0; i < choice_num; i++) {
      choices[i] = rhs.choices[i];  // check
    }
  }

  virtual ~ChoicePage() {}
  //destructor, the data structures used have their own destructors
  // Add the choice to the vector

  virtual std::string get_page_type() { return "N"; }  // facilitates choice addition

  virtual void add_choice_option(size_t page_number,
                                 size_t page_destination,
                                 std::string choice_text) {
    assert((page_num == page_number) &&
           "This is not the right page for choice insertion");
    std::cout << "\nThe choice version of add choice option was triggered\n";
    std::cout << choices.size() << "is the size of the choices vector prior to adding\n";

    std::pair<std::string, size_t> choice_with_destination;

    choice_with_destination.first = choice_text;

    choice_with_destination.second = page_destination;

    choices.push_back(choice_with_destination);

    choice_num++;
    std::cout << choices.size() << "is the size of the choices vector\n";
    std::cout << "For page -" << page_num << "- the choice is -"
              << choice_with_destination.first << "- and the destination is -"
              << choice_with_destination.second << "-Choice num is -" << choice_num
              << "- and now let me show myself the vector results -"
              << choices[choice_num - 1].first << "- second -"
              << choices[choice_num - 1].second << "- That's it for now\n\n";
  }

  virtual Page * deep_copy() {  // used to be virtual
    ChoicePage * copy_to_return = new ChoicePage(text, page_num);
    copy_to_return->choices.resize(choices.size());
    //copy_to_return->choices = choices;
    copy_to_return->choice_num = choice_num;
    for (size_t i = 0; i < choice_num; i++) {
      copy_to_return->choices[i] = choices[i];  // check
    }

    return copy_to_return;
  }

  virtual void print_page() {
    // Prints the contents of the page according to the README
    // Page number first, then contents.

    std::cout << "Page " << page_num << "\n"
              << "==========\n"
              << text << "\n"
              << "What would you like to do?";

    assert(choice_num == choices.size() && "Your choice num is wrong\n");
    for (size_t i = 0; i < choice_num; i++) {
      //
      std::cout << "\n"
                << " " << i + 1 << ". " << choices[i].first;
    }
  }
};

class TerminalPage : public Page {
  // This is the version of the page that ends the story

  bool win_lose_flag;  // this determines the final message

 public:
  TerminalPage() : Page(), win_lose_flag(false){};

  TerminalPage(std::string page_body, size_t page_num, bool is_win) :
      Page(page_num, page_body), win_lose_flag(is_win) {}

  TerminalPage(const TerminalPage & rhs) :
      //Page(rhs.text, rhs.page_num),
      // text(rhs.text),
      // page_num(rhs.page_num),
      //choices(rhs.choices),
      win_lose_flag(rhs.win_lose_flag) {
    //
    text = rhs.text;
    page_num = rhs.page_num;
  }

  virtual ~TerminalPage() {}
  //destructor, the data structures used have their own destructors

  virtual Page * deep_copy() {  // used to be virtual
    TerminalPage * copy_to_return = new TerminalPage(text, page_num, win_lose_flag);

    return copy_to_return;
  }

  virtual std::string get_page_type() { return "WL"; }

  virtual void print_page() {
    // Prints the contents of the page according to the README
    // Page number first, then contents.

    std::cout << "Page " << page_num << "\n"
              << "==========\n"
              << text << "\n";

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
  // this is a story class that stores the
  // the story pages

 protected:
  std::vector<Page *> story_pages;
  size_t page_count;

 public:
  Story() :
      page_count(
          0){};  // only a default constructor is necessary, as no arguments will be taken

  Story(const Story & rhs) {
    // Takes in rhs to construct a Story object
    page_count = rhs.get_page_count();

    story_pages.resize(page_count);

    for (size_t i = 0; i < rhs.get_page_count(); i++) {
      //
      story_pages[i] = rhs.story_pages[i]->deep_copy();
    }
  }

  ~Story() {
    // Free all the memory allocated for every single page

    for (size_t i = 0; i < page_count; i++) {
      delete story_pages[i];
    }
  };

  size_t get_page_count() const { return page_count; }  // returns page count

  void add_page(Page * some_page) {
    // Adds page to the story
    page_count = page_count + 1;
    story_pages.resize(page_count);
    story_pages[page_count - 1] = some_page;
    // add error checks
  }

  // Page *& find_choice_page(size_t page_index) {
  //   // returns reference to page pointer

  //   //assert(page_index < page_count && "Index is out of range");

  //   for (size_t i = 0; i < page_count; i++) {
  //     if (story_pages[i]->get_page_num() == page_index) {
  //       return story_pages[i];
  //     }
  //   }

  //   std::cerr << "Requested page-" << page_index << "-not found.\n";
  //   exit(EXIT_FAILURE);
  // };

  void add_choice(std::string choice_text, size_t page_number, size_t destination) {
    // Adds a choice to the given page if it exists
    //   //assert(page_index < page_count && "Index is out of range");

    bool found = false;
    for (size_t i = 0; i < page_count; i++) {
      if (story_pages[i]->get_page_num() == page_number) {
        // std::cout << "Hey, Eric, I made it here to add choice, page is found"
        //           << std::endl;
        assert(story_pages[i]->get_page_type() == "N" && "Page is not a choice page\n");
        story_pages[i]->add_choice_option(page_number, destination, choice_text);
        found = true;
      }
    }

    if (!found) {
      std::cerr << "Requested page-" << page_number << "-not found.\n";
      exit(EXIT_FAILURE);
    }

    //   ChoicePage * choice_page = find_page(page_number);

    //   assert(choice_page->get_page_type() == "N" && "Page is not a choice page\n");

    //   choice_page->add_choice_option();
    //   // size_t page_number, size_t page_destination, std::string choice_text) {
    //   // assert((page_num == page_number) &&
    //   //        "This is not the right page for choice insertion");

    //   // std::pair<std::string, size_t> choice_with_destination;

    //   // choice_with_destination.first = choice_text;

    //   // choice_with_destination.second = page_destination;

    //   // choices.push_back(choice_with_destination);

    //   // choice_num++;
    // }
  }
  void print_story() {
    // Prints all the story pages using their respective printing methods
    for (size_t i = 0; i < page_count; i++) {
      story_pages[i]->print_page();
    }
  }
};

// Functions

std::string combine_dir_file_names(char * dir_name, std::string name_of_file);

int directory_file_exists(char * some_arg, std::string name_of_file);

char * file_charname(char * dir_name, std::string name_of_file);
std::string file_to_string(char * dir_name, std::string name_of_file);
bool is_declaration_requirment_met(std::string some_str);
bool is_page_declaration(std::string story_line, char * dirname);

void parse_declaration(std::string story_line, char * dirname);
Page * parse_declaration_page(std::string story_line, char * dirname);
bool is_choice_page(std::string story_line);

//void parse_choice_line(std::string story_line);
//Page *  parse_declaration_page(std::string story_line, char * dirname) {

void parse_choice_line(std::string story_line, Story & a_story);

bool is_whitespace_line(std::string line);

#endif
