/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Assembler program that transforms Hack assembly code into its 
 *                  corresponding binary code.
 *
 *        Version:  1.0
 *        Created:  02/13/2022 14:24:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alejandro Gomez, 
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "symbolTable.h"
#include "assembler.h"
int getword(char *, int);

#define COMMENT //
#define C_SEPERATOR ;
#define C_EQUALS =
#define PARENS (

void runFile(char *filename) {
  FILE *fp = NULL;
  char *buffer = NULL;
  struct keytab_list symbol_table;
  size_t len;
  int buffer_len;

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Could not open file.\n");
    exit(1);
  }

  // Put file contents in a buffer for processing
  if ((buffer_len = getdelim( &buffer, &len, '\0', fp)) == -1) {
    fprintf(stderr, "Error: could not read file into buffer\n");
    exit(1);
  }

  // remove comments and empty break lines
  char *processed_file = process_buffer(buffer, buffer_len);
 
  printf("%s", processed_file);
  // extract labels and put in variables  
  //extract_labels(processed_file, &symbol_table);
  
  // parse file and write out binary output file
  //parse(processed_file, variables);
  // free(cleaned_input)
  free(processed_file);
  free(buffer); 
  freeList(&symbol_table);
  fclose(fp);
}



int main(int argc, char **argv) 
{
   if (argc != 2) {
    fprintf(stderr, "Please provide a file.\n");
    exit(1);
  } else {
    if (assemble(argv[1])) {
      printf("Successfully processed file.");
    } else {
      fprintf(stderr, "Error: Could not process file.");
      exit(1);
    }
  }
  return 0;
}
