#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

bool parse(char *processed_file, struct keytab_list *variables) {
  int i = 0, j = 0;
  while (processed_file[i] != EOF) {
    // is A instruction or variable
    if (processed_file[i] == '@') {
      // get label, check if it is a valid number. If so, it is an A instruction
      i++; // consume '@'

      j = i;
      while (processed_file[j] != '\n')
        j++; // every command is guranteed to be delimited by a new line.

      char *tmp = malloc((j-i+1)*sizeof(char));
      strlcpy(tmp, (processed_file+i), (j-i));
      int value = atoi(tmp);
      if (value != -1) {
        // convert to binary and print
      } else {
        // is not a number, add as variable to symbol table
        addVariable(variables, tmp);
      }
    }
  }
  return true;
}
