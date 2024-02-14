#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_to_str_writer(char * out_string,
                       size_t out_start,
                       const char * original_string,
                       size_t original_size,
                       size_t original_start) {
  // writes chars in new string based on original string
  // assumes the new string has the size to hold the original
  for (size_t i = 0; i < original_size; i++) {
    out_string[out_start + i] = original_string[original_start + i];
  }

  return;
}

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  // Function to generate output file name
  const char count_str[] = ".counts";
  size_t str_size = strlen(inputName);
  size_t count_size = strlen(count_str);
  size_t output_sz = str_size + count_size;

  char * output_name = malloc((output_sz + 1) * sizeof(*output_name));

  str_to_str_writer(output_name, 0, inputName, str_size, 0);
  str_to_str_writer(output_name, str_size, count_str, count_size, 0);

  output_name[output_sz] = '\0';

  return output_name;
}
