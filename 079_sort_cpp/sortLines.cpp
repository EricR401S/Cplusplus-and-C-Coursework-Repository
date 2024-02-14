#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

// writing the sortlines implementation

std::vector<std::string> file_to_vector_string(std::istream & input) {
  // read every line from this stream

  std::vector<std::string> my_vector_strings;

  std::string placeholder;

  while (std::getline(input, placeholder)) {
    my_vector_strings.push_back(placeholder);
  }

  // std::cout << "Eric, this works man" << std::endl;

  std::sort(my_vector_strings.begin(), my_vector_strings.end());
  // return a reference to the super vector

  for (size_t i = 0; i < my_vector_strings.size(); i++) {
    std::cout << my_vector_strings[i] << std::endl;
  }
  return my_vector_strings;
}

//general algorithm

// read from input or read from file, figure this part out

//
//

// sort the vector

// for string in that vector, print everything, with std::cout

int main(int argc, char ** argv) {
  // do somethign for agrc == 1
  if (argc == 1) {
    // do stuff
    //std::ofstream otherfile(std::cin);
    file_to_vector_string(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      // do other stuff
      std::ifstream myfile(argv[i]);
      if (myfile.is_open()) {
        //do the actual printing and sorting
        file_to_vector_string(myfile);
      }
      else {
        std::cerr << " your file does not exist" << std::endl;
        exit(EXIT_FAILURE);
      }
      // consider erroring out
      myfile.close();
    }
    return EXIT_SUCCESS;
  }
}
//   // arg 1 case
//   // remember to close file, throw error if necessary
//   if (argc == 1) {
//     std::string s;
//     std::cin >> x;
//     if (!std::cin.good()) {
//       std::cin.clear();
//       std::string badinput;
//       std::cin >> badinput;
//       if (!std : good())){
//           file_to_string_array(stdin);
//         }

//       // arg greater than 1 case - for loop
//       // remmeber to close file, throw error if necessary
//       else {
//       }

//       return EXIT_SUCCESS;
//     }
