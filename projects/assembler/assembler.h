#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdlib.h>

bool assemble(char *);
char *process_buffer(char *, size_t);
void extract_labels(char *, struct keytab_list *);

#endif
