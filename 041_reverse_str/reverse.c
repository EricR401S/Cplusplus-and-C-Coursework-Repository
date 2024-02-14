#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  if (str == NULL) {
    return;  //exit(EXIT_FAILURE)
  }
  size_t size_of_str = strlen(str);  // excludes the null terminator
  char rev_copy[size_of_str +
                1];  // take the size and add one more for the null terminator
  size_t other_counter = 0;
  char * new_ptr = str;
  if (size_of_str == 0) {
    return;
  }

  for (int i = size_of_str - 1; i >= 0;
       i--) {  //size of str, that index should be the one before the null terminator
    rev_copy[other_counter] = new_ptr[i];  // used to be str
    other_counter++;  // ends with the index of the final box in for rev_copy
  }
  char * ptr = str;  // point to the same place as str

  // counting from 0 to N exclusive
  for (size_t j = 0; str[j] != '\0'; j++) {
    ptr[j] = rev_copy[j];
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
