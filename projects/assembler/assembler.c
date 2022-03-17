#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "symbolTable.h"
#include "assembler.h"
#include "parser.h"

bool assemble(char *filename) {
  FILE *fp = NULL;
  char *buffer = NULL;
  struct keytab_list symbol_table;
  size_t len;
  int buffer_len;

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Could not open file.\n");
    return false;
  }

  // Put file contents in a buffer for processing
  if ((buffer_len = getdelim( &buffer, &len, '\0', fp)) == -1) {
    fprintf(stderr, "Error: could not read file into buffer\n");
    return false;
  }

  pre_populate_symbol_table(&symbol_table);

  // remove comments and empty break lines
  char *processed_file = process_buffer(buffer, buffer_len);
  
  // extract labels and put in variables
  extract_labels(processed_file, &symbol_table);
 
  // parse file and write out binary output file
  parse(processed_file, symbol_table);

  free(processed_file);
  free(buffer);
  freeList(&symbol_table);
  fclose(fp);
  return true;
}

char *process_buffer(char *buffer, size_t buffer_len) {
  int fast = 0, slow = 0;
  char *processed_file = NULL;
  
  if ((processed_file = malloc(sizeof(char)*buffer_len)) == NULL) {
    fprintf(stderr, "Error: ran out of memory during process_buffer alloc");
    exit(1);
  }

  // remove comments
  while (buffer[fast] !='\0') {
    if (buffer[fast] == '/') {
      while (buffer[fast] != '\n')
        fast++;
    } else if (buffer[fast] == '\r') {
        fast++;
    } else {
      processed_file[slow++] = buffer[fast++];
    }
  }

  // Find line where commands begin
  slow = fast = 0;
  while (processed_file[fast] == '\n' && processed_file[fast+1] == '\n')
    fast++;
  fast++;

  // remove empty blanks
  while (processed_file[fast] != '\0')
    processed_file[slow++] = processed_file[fast++];

  // terminated buffer after new length
  processed_file[slow] = '\0';

  // reallocate buffer to be new length
  processed_file = realloc(processed_file,sizeof(char)*(slow));

  return processed_file;
}

void extract_labels(char *program, struct keytab_list *symbol_table) {
  size_t i = 0, j = 0, lineCount = 1;
  char *label = NULL;
  while (program[i] != EOF) {
    if (program[i] == '(') {
      i++; // consume parenthesis
      
      j = i;
      
      while (program[j++] != ')') // look-ahead to get label length
        ;
      j--; // remove closing bracket

      if ((label = malloc((j-i+1)*sizeof(char))) == NULL) {
        fprintf(stderr, "Error: could not allocate memory.");
        exit(1);
      }

      memcpy(label, (program+i), (j-i));
      printf("%s\n", label);
      insert(symbol_table, label, lineCount); 
    }
    if (program[i] == '\n') lineCount++;
    i++;
  }
}
