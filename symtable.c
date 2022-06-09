#include "cons.h"
#include "cache.h"
#include "symtable.h"
#include <string.h>


value *sym_lookup(symbol *table, char *name) {
    for (symbol *s = table; s != (symbol *)0; s = s->next) {
        if(!strcmp(s->name, name)) {
            return s->v;
        }
    }

    return (value *)0;
}


value *eval(symbol *table, cons *c) {
    if(c->car.type == t_defun) {
        if(c->cdr.type == t_cons) {
            return c->car.fn(eval(table, c->cdr.cons));
        } else {
            printf("eval fn...");
            return c->car.fn(&c->cdr);
        }
    } else if (c->car.type == t_symbol) {
        c->car = *sym_lookup(table, c->car.symbol);
        return eval(table, c);
    }
    return (value *)0;
}


symbol *sym_set(symbol *table, char *name, value *v) {
    
}
