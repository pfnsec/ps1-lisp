#include "cons.h"
#include "cache.h"
#include "symtable.h"
#include "prelude.h"
#include <string.h>
#include <stdio.h>


value *sym_lookup(symbol *table, char *name) {
    for (symbol *s = table; s != (symbol *)0; s = s->next) {
        if(!strcmp(s->name, name)) {
            return s->v;
        }
    }

    printf("Symbol %s undefined \n", name);
    return (value *)0;
}


value *eval(symbol *table, value *v) {
    if(IS_CONS(v)) {
        if(IS_DEFUN(CAR(v))) {
            if(IS_CONS(CDR(v))) {
                return CAR(v)->fn(eval(table, CDR(v)));
            } else {
                return CAR(v)->fn(CDR(v));
            }

        } else if (IS_SYMBOL(CAR(v))) {
            return eval_symbol(table, v);
        }
    } else {
        return v;
    }

    return v;
}

value *eval_symbol(symbol *table, value *v) {
    if(!strcmp(CAR(v)->symbol, "map")) {

        value *fn = sym_lookup(table, CADR(v)->symbol);

        for(value *vi = CDDR(v); !IS_NIL(vi); vi = CDR(vi)) {
            *CAR(vi) = *fn->fn(CAR(vi));
        }

        return CDDR(v);
    } else if(!strcmp(CAR(v)->symbol, "if")) {
        printf("if: {\n");
        value *cond = CADR(v);
        value *then = CAR(CDDR(v));
        print_value(v);
        printf("\n");
        print_value(cond);
        printf("\n");
        print_value(then);
        printf("\n");
        printf("}\n");

    } else {
        *CAR(v) = *sym_lookup(table, CAR(v)->symbol);
        return eval(table, v);
    }
}




symbol *sym_set(symbol *table, char *name, value *v) {
    
}
