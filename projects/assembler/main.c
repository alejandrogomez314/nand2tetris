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


// Key-val struct of a symbol with its corresponding address
struct keytab {
  char *symbol;
  int address;
}; 

// must be alphabetically ordered in order to perform bsearch
struct keytab predefinedSymbols[] = {
  { "ARG", 2 },
  { "KBD", 24576 },
  { "LCL", 1 },
  { "R0", 0 }, 
  { "R1", 1 },
  { "R2", 2 },
  { "R3", 3 },
  { "R4", 4 },
  { "R5", 5 },
  { "R6", 6 },
  { "R7", 7 },
  { "R8", 8 },
  { "R9", 9 },
  { "R10", 10 },
  { "R11", 11 },
  { "R12", 12 },
  { "R13", 13 },
  { "R14", 14 },
  { "R15", 15 },
  { "SCREEN", 16384 },
  { "SP", 0 },
  { "THAT", 4 },
  { "THIS", 3 }
};

// Stores destination. Values must translated to binary in instruction
struct keytab destination[] = {
  { "A", 4  },   // A register
  { "AD", 6 },  // A register and D register
  { "AM", 5 },  // A register and RAM[A]
  { "AMD", 7}, // A register, RAM[A] and D register
  { "D", 2  },   // D register
  { "M", 1  },   // RAM[A]
  { "MD", 3 } // RAM[A] and D register
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

// stores comp for a=1. Values must be translated to binary in instruction
struct keytab comp0[] = {
 { "0", 42 },
 { "1", 63 },
 { "-1", 50 },
};

// translate integers up to 32768 to its 16-bit padded equivalent. numbers outside range are thrown as errors. 
char *itoa(int n, char *s)
{

}

// a binary search method to find the value in a keytab given a word key
int get(char *symbol, struct keytab keytab[], int n)
{
   int cond;
   int low, high, mid;
   
   low = 0;
   high = n-1;
   while (low <= high)
   {
      mid = (low + high) / 2;
      if ((cond = strcmp(symbol, keytab[mid].symbol)) < 0)
        high = mid - 1;
      else if (cond > 0)
        low = mid + 1;
      else
        return keytab[mid].address;
   }
   return -1;
}

#define COMMENT "//"
#define C_SEPERATOR ";"
#define C_EQUALS "="


int main(int argc, char **argv) 
{

  printf("Address: %d\n", get("AM", destination, sizeof destination / sizeof(struct keytab)));
  printf("Address: %d\n", get("A", destination, 7));
  printf("Address: %d\n", get("M", destination, 7));
  printf("Address: %d\n", get("MD", destination, 7));
  return 0;
}
