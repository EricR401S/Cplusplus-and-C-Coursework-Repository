#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sunspots.h"

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
        printf("The date can only have digits\n");
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
      printf("Newline not at end of string\n");
      exit(EXIT_FAILURE);
    }

    else if ((sunspot_string[i] == '\n') && (i == n - 1)) {
      continue;
    }

    else if (sunspot_string[i] == ' ') {
      continue;
    }

    else {
      printf("Improper formatting of sunspot average\n");
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
        printf("Decimal values have only one period\n");
        exit(EXIT_FAILURE);
      }

      // a period ended the string
      if (i == n - 1) {
        printf("Improper formatting of sunspot average\n");
        exit(EXIT_FAILURE);
      }

      continue;
    }

    else if (sunspot_string[i] == ' ') {
      //check if whitespaces continue unto the end of string
      whitespace_checker(sunspot_string, i, n);
      break;  // no error was triggered
    }

    else {
      // improper characters catch
      printf("Use of non-numbers for sunspot average, E\n");
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
  printf("Show me trouble : %s", line);
  // empty input catch
  if (line == NULL) {
    printf("Do not provide Null inputs\n");
    exit(EXIT_FAILURE);
  }

  // exclude null terminator
  size_t str_size = strlen(line);

  // emptyness or non-fullness catch
  if (str_size < 9) {
    printf(
        "The year must contain 4 digitsm, the month 2 digits, and a sunspot numbers\n");
    exit(EXIT_FAILURE);
  }

  // catch violations of month and year
  // inputs via indices

  if ((line[4] != '-') || (line[7] != ',')) {
    printf("Year is in 4 digits, and month is in 2 digits.\n");
    exit(EXIT_FAILURE);
  }

  // if none of these checks were trigerred,
  // verify the integrity of the string

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
    printf("Not a valid month number between 01 and 12");
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

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  return 0;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  return 0;
}

int main() {
  char * s = "1755-01,17.0";
  ss_monthly_t result = parseLine(s);
  printf("The year is totally %d", result.year);
}
