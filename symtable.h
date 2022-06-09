#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "cons.h"

typedef struct symbol {
    char *name;
    value *v;
    struct symbol *next;
} symbol;


#define SYMBOL_END (struct symbol *)0
#define SYMBOL_ENTRY(__name, __value, __next) &(symbol){.name = __name, .v = __value, .next = __next}

#define SYMBOL_LIST(__name, __value, args...) SYMBOL_ENTRY(__name, __value, SYMBOL_LIST(args))

value *sym_lookup(symbol *table, char *name);
symbol *sym_set(symbol *table, char *name, value *v);

value *eval(symbol *table, cons *c);

#endif
