// incldue library
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main () {
    number_of_rows = get_rows("GlobalTemperatures.csv");
}

int get_rows (char str[1000]) {
    int get_length(char str[1000]) {
  FILE *input;
  int count = 0;
  char buffer[1000];
  input = fopen(str, "r");
  while (fgets(buffer, sizeof(buffer), input)) {
    count += 1;
  }
  fclose(input);
  return count - 2;
}
}