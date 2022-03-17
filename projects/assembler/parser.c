#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

bool isValidNumber(char *);
char *convertToBin(int);
char *pad16(int);

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
      if (isValidNumber(tmp)) {
        // convert to binary and print
        int value = atoi(tmp);
        printf("%d\n", pad16(convertToBin(value)));
      } else {
        // is not a number, add as variable to symbol table
        addVariable(variables, tmp);
      }
      free(tmp);
    }
  }
  return true;
}

bool isValidNumber(char *str) {
  int i = 0;
  while (str[i] != EOF) {
    if (str[i] < '0' || str[i] > '9') return false;
    i++;
  }
  return true;
}

char *convertToBin(int num) {
  char *result = malloc(sizeof(char)*16); // max allowed size is 2^16 or 65536
  int i = 0;
  while (num != 0) {
    result[i] = num % 2;
    num /= 2;
    i++;
  }
  return result;
}
