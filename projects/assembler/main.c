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

struct keytab;
struct List;
int getword(char *, int);
void initList(struct List *, int);
void insert(struct List *, char *, int);
void freeList(struct List *);
void runFile(char *);
void populate_symbol_table(struct List *);

// Key-val struct of a symbol with its corresponding address.
struct keytab {
  char *symbol;
  int address;
};

struct List {
  struct keytab* array;
  int used;
  int size;
};

void initList(struct List *list, int initialSize) {
  (*list).array = malloc(initialSize*sizeof(struct keytab));
  (*list).used = 0;
  (*list).size = initialSize;
}

void insert(struct List *list, char *symbol, int address) {
  if ((*list).used == (*list).size) {
    (*list).size *= 2;
    (*list).array = realloc((*list).array, (*list).size*sizeof(struct keytab));
    if (!list->array) {
      free(list->array);
      printf("Ran out of memory.\n");
      exit(1);
    }
  }
  (*list).array[(*list).used].address = address;
  (*list).array[(*list).used].symbol = symbol;
  (*list).used += 1;
}

void freeList(struct List *list) {
  free((*list).array);
  (*list).array = NULL;
  (*list).used = (*list).size = 0;
}

// Stores destination. Values must translated to binary in instruction
struct keytab destination[] = {
  { "A", 4  },   // A register
  { "AD", 6 },   // A register and D register
  { "AM", 5 },   // A register and RAM[A]
  { "AMD", 7},   // A register, RAM[A] and D register
  { "D", 2  },   // D register
  { "M", 1  },   // RAM[A]
  { "MD", 3 }    // RAM[A] and D register
};

struct keytab jump[] = {
  { "JEQ", 2 },
  { "JGE", 3 },
  { "JGT", 1 },
  { "JLE", 6 },
  { "JLT", 4 },
  { "JMP", 7 },
  { "JNE", 5 },
};

// stores comp for a=0. Values must be translated to binary in instruction
struct keytab comp0[] = {
 { "!A", 49 },
 { "!D", 13 },
 { "0", 42 },
 { "-1", 50 },
 { "-A", 51 },
 { "-D", 15 },
 { "1", 63 },
 { "A", 48 },
 { "A+1", 55 },
 { "A-1", 50 },
 { "A-D", 7 },
 { "D", 12 },
 { "D&A", 0 },
 { "D+1", 31 },
 { "D+A", 2 },
 { "D-A", 19 },
 { "D|A", 21 },
};

struct keytab comp1[] = {
 { "!M", 49 },
 { "-M", 51 },
 { "M", 48 },
 { "M+1", 55 },
 { "M-1", 50 },
 { "M-D", 7 },
 { "D&M", 0 },
 { "D+M", 2 },
 { "D-M", 19 },
 { "D|M", 21 },
};

// translate integers up to 32768 to its 16-bit padded equivalent. numbers outside range are thrown as errors. 
//char *itoa(int n, char *s)
//{
//
//}

#define COMMENT //
#define C_SEPERATOR ;
#define C_EQUALS =
#define PARENS (

void extract_labels(char *program, struct List *symbol_table) {
  // loop over program. Put if there is a label, put it 
  // on the symbol table with the label as key and its line number
  // as the value
  //
}

void populate_symbol_table(struct List *symbol_table) {
  initList(&(*symbol_table), 16);
  insert(&(*symbol_table), "R0", 0);
  insert(&(*symbol_table), "R1", 1); 
  insert(&(*symbol_table), "R2", 2); 
  insert(&(*symbol_table), "R3", 3); 
  insert(&(*symbol_table), "R4", 4); 
  insert(&(*symbol_table), "R5", 5); 
  insert(&(*symbol_table), "R6", 6); 
  insert(&(*symbol_table), "R7", 7); 
  insert(&(*symbol_table), "R8", 8); 
  insert(&(*symbol_table), "R9", 9); 
  insert(&(*symbol_table), "R10", 10); 
  insert(&(*symbol_table), "R11", 11); 
  insert(&(*symbol_table), "R12", 12); 
  insert(&(*symbol_table), "R13", 13); 
  insert(&(*symbol_table), "R14", 14); 
  insert(&(*symbol_table), "R15", 15); 
  insert(&(*symbol_table), "SCREEN", 16384); 
  insert(&(*symbol_table), "KBD", 24576); 
  insert(&(*symbol_table), "SP", 0); 
  insert(&(*symbol_table), "LCL", 1); 
  insert(&(*symbol_table), "ARG", 2); 
  insert(&(*symbol_table), "THIS", 3); 
  insert(&(*symbol_table), "THAT", 4); 
}


char *process_buffer(char *buffer, int buffer_len) {
  int fast = 0, slow = 0;
  char *processed_file = malloc(sizeof(char)*buffer_len);
  
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
  processed_file[slow+1] = '\0';
 
  // reallocate buffer to be new length
  processed_file = realloc(processed_file,sizeof(char)*(slow+1));  

  return processed_file;
}

//void parse(char *program, struct keytab

void runFile(char *filename) {
  FILE *fp = NULL;
  char *buffer = NULL;
  struct List symbol_table;
  size_t len;
  int buffer_len;

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Could not open file.\n");
    exit(1);
  }

  // populate symbol table with pre-defined symbols
  populate_symbol_table(&symbol_table);

  // Put file contents in a buffer for processing
  if ((buffer_len = getdelim( &buffer, &len, '\0', fp)) == -1) {
    fprintf(stderr, "Error: could not read file into buffer\n");
    exit(1);
  }

  // remove comments and empty break lines
  char *processed_file = process_buffer(buffer, buffer_len);
 
  printf("%s", processed_file);
  // extract labels and put in variables  
  extract_labels(processed_file, &symbol_table);
  
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
    runFile(argv[1]);
  }
  return 0;
}
