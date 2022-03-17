#include <stdlib.h>
#include <stdbool.h>

struct keytab {
  char *symbol;
  int address;
};

struct keytab_list {
  struct keytab* array;
  size_t used;
  size_t size;
  size_t variableCursor;
};

void initList(struct keytab_list *, int);
bool insert(struct keytab_list *, char *, int);
void freeList(struct keytab_list *);
void pre_populate_symbol_table(struct keytab_list *);
bool addVariable(struct keytab_list *, char *);
