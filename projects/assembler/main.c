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

// Key-val struct of a symbol with its corresponding address. Used for fixed table.
struct keytab {
  char *symbol;
  int address;
}; 

struct node {
  char *symbol;
  int address;
  struct node *left;
  struct node *right;
};

int getword(char *, int);

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

struct node *talloc(void)
{
  return malloc(sizeof(struct node));
}

void insert(struct node *node, char *symbol, int address)
{
  int cond;

  if (node == NULL)
  {
    node = malloc(sizeof(struct node));
    *node->symbol = strdup(symbol);
    *node->address = address;
    *node->left = *node->right = NULL;
  }
  else if ((cond = strcmp(symbol, node->symbol)) == 0)
  {
    printf("Element already inserted\n");
    return; // @todo: throw an error?
  } 
  else if (cond < 0)
  {
    insert(node->left, symbol, address);
  } 
  else 
  {
    insert(node->right, symbol, address);
  }
}
void treeprint(struct node *node)
{
  if (node != NULL) {
    treeprint(node->left);
    printf("%s - %d\n", node->symbol, node->address);
    treeprint(node->right);
  }
}
struct node *populate_predefined_variables(struct node *variables) 
{
  insert(variables, "R0", 0);
  insert(variables, "R1", 1);
  insert(variables, "R2", 2);
  insert(variables, "R3", 3);
  insert(variables, "R4", 4);
  insert(variables, "R5", 5);
  insert(variables, "R6", 6);
  insert(variables, "R7", 7);
  insert(variables, "R8", 8);
  insert(variables, "R9", 9);
  insert(variables, "R10", 10);
  insert(variables, "R11", 11);
  insert(variables, "R12", 12);
  insert(variables, "R13", 13);
  insert(variables, "R14", 14);
  insert(variables, "R15", 15);
  insert(variables, "ARG", 2);
  insert(variables, "KBD", 24576);
  insert(variables, "LCL", 1);
  insert(variables, "SCREEN", 16384);
  insert(variables, "SP", 0);
  insert(variables, "THAT", 4);
  insert(variables, "THIS", 3);
  return variables;
}

int main(int argc, char **argv) 
{
  struct node *variables = NULL;
  // populate variables table
  //populate_predefined_variables(variables);
  insert(variables, "R0", 0);
  // do a first pass to extract label declaration 
  // extract_labels(variables);
  
  // parse file and write out binary output file
  // parse(root);
  
  treeprint(variables);
  return 0;
}
