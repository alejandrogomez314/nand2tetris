#include <stdio.h>
#include <stdbool.h>
#include "symbolTable.h"

void initList(struct keytab_list *list, int initialSize) {
  (*list).array = malloc(initialSize*sizeof(struct keytab));
  (*list).used = 0;
  (*list).size = initialSize;
  (*list).variableCursor = 15;
}

bool addVariable(struct keytab_list *list, char *symbol) {
  (*list).variableCursor += 1;
  return insert(list, symbol, list->variableCursor);
}

bool insert(struct keytab_list *list, char *symbol, int address) {
 // for (size_t i = 0; i < list->used; i++) {
 //   if (list->array[i].address == address
 //       && list->array[i].symbol == symbol) {
 //     return false;
 //   } 
 // }
  if ((*list).used == (*list).size) {
    (*list).size *= 2;
    (*list).array = realloc((*list).array, (*list).size*sizeof(struct keytab_list));
    if (!list->array) {
      free(list->array);
      printf("Ran out of memory.\n");
      exit(1);
    }
  }
  (*list).array[(*list).used].address = address;
  (*list).array[(*list).used].symbol = symbol;
  (*list).used += 1;
  return true;
}

void freeList(struct keytab_list *list) {
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

void pre_populate_symbol_table(struct keytab_list *symbol_table) {
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
