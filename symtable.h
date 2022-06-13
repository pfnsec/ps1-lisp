#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "cons.h"

typedef struct symbol {
    char *name;
    enum lifetime { t_static, t_dynamic } lifetime;
    value *v;
    struct symbol *next;
} symbol;


#define SYMBOL_END (struct symbol *)0
#define SYMBOL_ENTRY(__name, __value, __next) &(symbol){.name = __name, .v = __value, .next = __next}

#define SYMBOL_LIST(__name, __value, args...) SYMBOL_ENTRY(__name, __value, SYMBOL_LIST(args))

symbol *sym_lookup(symbol *table, char *name);
symbol *sym_set(symbol *table, char *name, value *v);
symbol *sym_unset(symbol *table, char *name);
void print_symtable(symbol *table);

value *eval(symbol *table, value *v);
value *eval_symbol(symbol *table, value *v);
value *eval_lambda(symbol *table, value *lambda, value *args);

#endif
