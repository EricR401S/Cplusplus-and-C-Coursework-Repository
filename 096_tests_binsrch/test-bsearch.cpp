#include <cstdlib>
#include <iostream>
#include <vector>

#include "function.h"
// int find_expected_ans(Function<int, int> * f, int low, int high) {
//   int highest = f->invoke(high - 1);

//   int lowest = f->invoke(low);

//   if (highest > 0 && lowest > 0) {
//     return low;
//   }

//   else if (highest < 0 && lowest < 0) {
//     return high - 1;
//   }

//   else {
//     int best_local_minimum = lowest;

//     int best_local_x = low;

//     for (int i = low; i < high; i++) {
//       int result = f->invoke(i);

//       if (result > best_local_minimum && result <= 0) {
//         best_local_minimum = result;
//         best_local_x = i;
//       }
//       else if (result > 0) {
//         break;  // prevents infinite searching
//       }
//     }

//     return best_local_x;
//   }
// }

// int find_expected_ans(Function<int, int> * f, int low, int high) {
//   // int highest = f->invoke(high - 1);

//   int lowest = f->invoke(low);

//   bool all_negative = true;

//   bool all_positive = true;

//   // if (highest > 0 && lowest > 0) {
//   //   return low;
//   // }

//   // else if (highest < 0 && lowest < 0) {
//   //   return high - 1;
//   // }

//   int best_local_minimum = lowest;

//   int best_local_x = low;

//   for (int i = low; i < high; i++) {
//     int result = f->invoke(i);

//     if (result > best_local_minimum && result <= 0) {
//       best_local_minimum = result;
//       best_local_x = i;
//     }
//     if (result > 0) {
//       all_negative = false;
//     }
//     else if (result < 0) {
//       all_positive = false;
//       // prevents infinite searching
//     }
//   }

//   if (all_positive) {
//     return low;
//   }
//   else if (all_negative) {
//     return high - 1;
//   }
//   else {
//     return best_local_x;
//   }
// }

// void check(Function<int, int> * f,
//            int low,
//            int high,
//            //int expected_ans,
//            //const char * mesg)
//            const std::string mesg) {
//   //
//   unsigned max_invocations;
//   if (high > low) {
//     max_invocations = log2(high - low) + 1;
//   }
//   else {
//     max_invocations = 1;
//   }

//   int expected_ans = find_expected_ans(f, low, high);

//   //CountedIntFn cfn = CountedIntFn(max_invocations, f, mesg);

//   bool found = false;
//   while (max_invocations > 0) {
//     if (binarySearchForZero(f, low, high) == expected_ans) {
//       found = true;
//       break;
//     }
//     max_invocations--;
//     std::cout << "movement detected" << max_invocations << "are remaining\n";
//   }
//   //while(cfn.invoke(int arg)
//   //cfn.invoke(int arg)

//   if (found) {
//     return;
//   }

//   else {
//     std::cerr << "Too many function invocations in " << mesg << "\n";
//     exit(EXIT_FAILURE);
//   }
// };

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  //const std::string mesg) {
  //
  unsigned max_invocations;
  if (high > low) {
    max_invocations = log2(high - low) + 1;
  }
  else {
    max_invocations = 1;
  }

  // int expected_ans = find_expected_ans(f, low, high);

  CountedIntFn cif(max_invocations, f, mesg);

  //int res = binarySearchForZero(&cif, low, high);

  int res = binarySearchForZero(&cif, low, high);

  while (binarySearchForZero(&cif, low, high) != expected_ans) {
    std::cout << "res is-" << res << "- for -" << mesg << "-\n";

    res = binarySearchForZero(&cif, low, high);
  };

  //std::cout << "res is-" << res << "- for -" << mesg << "-\n";

  // if (res != expected_ans) {  // 0
  //   // std::cerr << "Too many function invocations in " << mesg << "\n";
  //   std::cerr << "Function -" << mesg << "-failed to be binary searched\n";
  //   exit(EXIT_FAILURE);
};

int main(void) {
  LinFunctionA la;

  LinFunctionB lb;

  LinFunctionC lc;

  QuadFunctionA qa;

  QuadFunctionB qb;

  //std::vector<int> expected_answers_for_f = {0, -5, 20,
  std::vector<std::string> names_of_f = {
      "y=x", "y = 2x + 10", "5x - 100", "x^2 - 2x + 15", "x^2 + 4x + 4"};
  std::vector<Function<int, int> *> farr = {&la, &lb, &lc, &qa, &qb};

  check(&la, 0, 5, 0, "y=x");

  check(&la, -5, 0, -1, "y=x");

  check(&la, -5, 5, 0, "y=x");

  check(&la, -100, 100, 0, "y=x");

  check(&la, -100, -50, -49, "y=x");

  check(&la, 100, 150, 149, "y=x");

  //check(&la, -10, 1, "linear function A");

  // check(&la, 0, 100, "linear function A");

  // check(&la, -10, 0, "linear function A");

  // // lb

  // for (size_t i = 0; i < farr.size(); i++) {
  //   std::string mesg = "function";
  //   check(farr[i], -10, 1, "linear function");
  //   check(farr[i], -10, 0, "linear function");
  //   check(farr[i], -10, 10, "linear function");
  //   check(farr[i], -100, 100, "linear function");
  // }
  exit(EXIT_SUCCESS);
}
