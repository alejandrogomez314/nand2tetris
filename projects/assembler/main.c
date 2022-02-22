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

void extract_labels();

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

int isWhitespace(char c) {
  return c == ' ';
}

int isBlankLine(char c, FILE *fp) {
  return c == '\n' && c == fgetc(fp);
}

int isComment(char c, FILE *fp) {
  return c == '/' && c == fgetc(fp);
}

char *first_pass(FILE *fp) {
  int chunk = 4096;
  int counter = 0;
  char *buffer = malloc(chunk);
  char *test;
  int c;
  
  if (!buffer) exit(1);

  while ((c = fgetc(fp)) && (c != EOF)) {
    //if (isWhitespace(c) || isBlankLine(c, fp) || isComment(c, fp))
    //  continue;
    
    buffer[counter++] = c;
   
    if (counter == chunk) {
      chunk *= 2;
      test = realloc(buffer, chunk);
      if (!test) {
        free(buffer);
        exit(1);
      } else {
        buffer = test;
      }
    }
  }

  buffer[counter] = '\0';
  if (realloc(buffer, counter + 1) == NULL) {
    exit(1);
  }
  return buffer;
}

void runFile(char *filename) {
  FILE *fp = NULL;
  struct List symbol_table;
  
  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Could not open file.\n");
    exit(1);
  }

  // populate symbol table with pre-defined symbols
  populate_symbol_table(&symbol_table);

  // First run: remove comments, white spaces and extra break lines, add labels to symbols table with 
  // their corresponding line number;
  char *first = first_pass(fp);
  printf("%s\n", first); 
  // parse file and write out binary output file
  //char** second_pass = parse(first_pass, variables);
  // free(cleaned_input)
  // free(cleaned_input)
  
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
