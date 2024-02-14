#include "sunspots.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verify_Ss_digits(char * sunspot_string) {
  // Checks if strange characters are present
  // in the years or months

  for (size_t i = 0; i <= 7; i++) {
    size_t digit_bool = isdigit(sunspot_string[i]);

    if ((i == 4) || (i == 7)) {
      // this works in conjunction
      // with other conditional
      // statements in body of function
      continue;
    }
    else {
      if (digit_bool > 0) {
        continue;
      }

      else {
        perror("The date can only have digits\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  // if it the else condition continued unto here

  return;  // meaning all these numbers are valid digits
}

void whitespace_checker(char * sunspot_string, size_t start, size_t n) {
  // check for many consecutive whitespaces

  // one final newline is acceptable
  for (size_t i = start; i < n; i++) {
    if ((sunspot_string[i] == '\n') && (i != n - 1)) {
      perror("Newline not at end of string\n");
      exit(EXIT_FAILURE);
    }

    else if ((sunspot_string[i] == '\n') && (i == n - 1)) {
      continue;
    }

    else if (sunspot_string[i] == ' ') {
      continue;
    }

    else {
      perror("Improper formatting of sunspot average\n");
      exit(EXIT_FAILURE);
    }
  }
}
void verify_Ss_average(char * sunspot_string, size_t n) {
  //Check if strange characters are present
  //sunspot averages

  // a one time period counter
  int period_counter = 0;

  for (size_t i = 8; i < n; i++) {
    int digit_bool = isdigit(sunspot_string[i]);

    if (digit_bool > 0) {
      continue;
    }

    else if (sunspot_string[i] == '.') {
      period_counter++;

      if (period_counter > 1) {
        perror("Decimal values have only one period\n");
        exit(EXIT_FAILURE);
      }

      // a period ended the string
      if (i == n - 1) {
        perror("Improper formatting of sunspot average\n");
        exit(EXIT_FAILURE);
      }

      continue;
    }

    else if (sunspot_string[i] == '\n') {
      continue;
    }

    else if (sunspot_string[i] == ' ') {
      //check if whitespaces continue unto the end of string
      whitespace_checker(sunspot_string, i, n);
      break;  // no error was triggered
    }

    else {
      // improper characters catch
      perror("Use of non-numbers for sunspot average, E\n");
      exit(EXIT_FAILURE);
    }
  }
}

void fill_int_arr(char * new_array,
                  char * original_array,
                  size_t end,
                  size_t original_start) {
  // Fill in the new char array with int chars from the original array
  for (size_t i = 0; i < end; i++) {
    new_array[i] = original_array[original_start + i];
  }
  // to make into string
  new_array[end] = '\0';

  return;
}

void fill_avg_arr(char * new_array,
                  char * original_array,
                  size_t end,
                  size_t original_start) {
  // Fill in the new char array with float chars from the original array
  size_t counter_average = 0;

  for (size_t i = 0; i < end; i++) {
    if ((original_array[original_start + i] == ' ') ||
        (original_array[original_start + i] == '\n')) {
      counter_average = i;

      break;
    }

    new_array[i] = original_array[original_start + i];
  }
  // to make into string
  new_array[counter_average + 1] = '\0';

  return;
}

ss_monthly_t parseLine(char * line) {
  // Return ss_monthly_struct for parsed string
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;
  char average_array[100] = {0};
  //printf("Show me trouble : %s", line);
  // empty input catch
  if (line == NULL) {
    perror("Do not provide Null inputs\n");
    exit(EXIT_FAILURE);
  }

  // exclude null terminator
  size_t str_size = strlen(line);

  // emptyness or non-fullness catch
  if (str_size < 9) {
    perror(
        "The year must contain 4 digitsm, the month 2 digits, and a sunspot numbers\n");
    exit(EXIT_FAILURE);
  }

  // catch violations of month and year
  // ',' and '-' will belong to certain indices
  // within the correct format.

  if ((line[4] != '-') || (line[7] != ',')) {
    perror("Year is in 4 digits, and month is in 2 digits.\n");
    exit(EXIT_FAILURE);
  }

  // if none of these checks were trigerred,
  // verify the integrity of the string,
  // meaning no bad char in year
  // month and average

  verify_Ss_digits(line);
  verify_Ss_average(line, str_size);

  // creating the num arrays to convert to numbers
  char year_array[5] = {0};
  fill_int_arr(year_array, line, 4, 0);
  unsigned year_parsed = atoi(year_array);

  char month_array[3] = {0};
  fill_int_arr(month_array, line, 2, 5);
  unsigned month_parsed = atoi(month_array);

  if ((month_parsed <= 0) || (month_parsed > 12)) {
    perror("Not a valid month number between 01 and 12");
    exit(EXIT_FAILURE);
  }
  //size_t count = 0;
  //count = str_size - 8;
  fill_avg_arr(average_array, line, 100, 8);
  char * endptr;
  double avg_parsed = strtod(average_array, &endptr);

  ans.year = year_parsed;
  ans.month = month_parsed;
  ans.num = avg_parsed;

  return ans;
}

size_t filter_left(size_t num, size_t range) {
  if (num >= range) {
    return range;
  }

  else {
    return filter_left(num, range - 1);
  }
}

size_t filter_right(size_t num, size_t range, size_t array_size) {
  if ((array_size - 1) >= (num + range)) {
    return range;
  }

  else {
    return filter_right(num, range - 1, array_size);
  }
}
void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // Function to return array containing mean filtered values of the original
  // depending on the width

  // Error checks

  if ((data == NULL) || (mean == NULL)) {
    perror("Missing input arrays\n");
    exit(EXIT_FAILURE);
  }

  else if (n == 0) {
    perror("Empty array is not allowed\n");
    exit(EXIT_FAILURE);
  }

  //check partially empty array, could not figure it out

  else if (w % 2 != 1) {
    perror("W has to be an odd positive integer\n");
    exit(EXIT_FAILURE);
  }

  else if (w > n) {
    perror("W cannot be greater than n\n");
    exit(EXIT_FAILURE);
  }

  // fix for w 1

  for (size_t i = 0; i < n; i++) {
    ss_monthly_t ans;
    double filter_ans = 0;
    size_t range = w / 2;
    size_t left_range = filter_left(i, range);
    size_t right_range = filter_right(i, range, n);

    for (size_t j = (i - left_range); j < (i + right_range + 1); j++) {
      filter_ans += (data[j]).num;
    }
    size_t denominator = (i + right_range + 1) - (i - left_range);
    filter_ans /= denominator;
    ans.num = filter_ans;
    ans.year = (data[i]).year;
    ans.month = (data[i].month);
    mean[i] = ans;
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // Function that generates timestamp for ss_monthly_struct
  // with highest sunspot average from data

  // check for null or empty arrays
  if (data == NULL) {
    perror("Missing input arrays\n");
    exit(EXIT_FAILURE);
  }

  else if (n == 0) {
    perror("Empty array is not allowed\n");
    exit(EXIT_FAILURE);
  }

  // find the local max
  // start by using the first element in
  // data as placeholder max value

  size_t location = 0;

  double max_value = (data[0]).num;

  for (size_t i = 0; i < n; i++) {
    if ((data[i]).num > max_value) {
      location = i;
      max_value = (data[i]).num;
    }
  }

  double timestamp = (data[location]).year + (data[location]).month / 12.0;

  return timestamp;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  // Function that returns the average difference
  // across a period of sunspots timestamps

  // check for null or empty arrays
  if (timeStamps == NULL) {
    perror("Missing input arrays\n");
    exit(EXIT_FAILURE);
  }

  else if (n < 2) {
    perror("Empty array or array with 1 element are not valid input\n");
    exit(EXIT_FAILURE);
  }

  double avg_difference = 0.0;

  for (size_t i = 1; i < n; i++) {
    avg_difference += (timeStamps[i] - timeStamps[i - 1]);
    // considering adding abs((timeStamps[i] - timeStamps[i-1]))
    // not sure yet
  }

  avg_difference /= (n - 1);

  return avg_difference;
}
