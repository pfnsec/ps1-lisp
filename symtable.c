#include "cons.h"
#include "cache.h"
#include "symtable.h"
#include "prelude.h"
#include <string.h>
#include <stdio.h>


static symbol *symbol_last;

symbol *sym_lookup(symbol *table, char *name) {
    for (symbol *s = table; s != SYMBOL_END; s = s->next) {
        if(s->next == SYMBOL_END) {
            symbol_last = s;
        }

        if(!strcmp(s->name, name)) {
            return s;
        }
    }

    return (symbol *)0;
}


value *eval(symbol *table, value *v) {
    if(IS_CONS(v)) {
        if(IS_DEFUN(CAR(v))) {
            value *res = CAR(v)->fn(eval(table, CDR(v)));
            return res;

        } else if (IS_LAMBDA(CAR(v))) {
            return eval_lambda(table, CAR(v), eval(table, CDR(v)));

        } else if (IS_SYMBOL(CAR(v))) {
            return eval_symbol(table, v);

        } else {
            value *subs = value_alloc();
            subs->type = t_cons;
            subs->cons = cons_alloc();
            *CAR(subs) = *eval(table, CAR(v));
            *CDR(subs) = *eval(table, CDR(v));
            return subs;
        }
    } else if(IS_SYMBOL(v)) {
        return sym_lookup(table, v->symbol)->v;
    } else {
        return v;
    }

    return v;
}

value *eval_symbol(symbol *table, value *v) {
    if(!strcmp(CAR(v)->symbol, "map")) {

        value *fn = eval(table, CADR(v));
        value *args = eval(table, CAR(CDDR(v)));

        if(IS_DEFUN(fn)) {
            for(value *vi = CDDR(v); !IS_NIL(vi); vi = CDR(vi)) {
                *CAR(vi) = *fn->fn(CAR(vi));
            }
            return CDDR(v);
        } else if(IS_LAMBDA(fn)) {

            for(value *vi = CAR(CDDR(v)); !IS_NIL(vi); vi = CDR(vi)) {
                *CAR(vi) = *eval_lambda(table, fn, CAR(vi));
            }
            return CDDR(v);
        }


    } else if(!strcmp(CAR(v)->symbol, "define")) {
        char  *name = CADR(v)->symbol;
        value *val = eval(table, CAR(CDDR(v)));
        return sym_set(table, name, val)->v;

    } else if(!strcmp(CAR(v)->symbol, "lambda")) {
        CDR(v)->type = t_lambda;
        return CDR(v);
    } else if(!strcmp(CAR(v)->symbol, "if")) {
        value *cond = CADR(v);
        value *body = CDDR(v);

        value *pred = eval(table, cond);

        // nil and 0 are 'falsey' values
        if(IS_NIL(pred) || (IS_WORD(pred) && !pred->word)) {
            return eval(table, CADR(body));
        } else {
            return eval(table, CAR(body));
        }

    } else {
        value *subs = value_alloc();
        subs->type = t_cons;
        subs->cons = cons_alloc();
        *CAR(subs) = *sym_lookup(table, CAR(v)->symbol)->v;
        *CDR(subs) = *eval(table, CDR(v));
        value *res = eval(table, subs);
        return res;
    }
}


value *eval_lambda(symbol *table, value *lambda, value *args) {
    value *params = CAR(lambda);
    value *body = CDR(lambda);

    // Iterate over the params (pi) and supplied args (ai)
    value *pi;
    value *ai;
    for(
        pi = params, ai = args; 
        (!IS_NIL(pi) && !(IS_NIL(ai))); 
        pi = CDR(pi), ai = CDR(ai)
    ) {
        sym_set(table, CAR(pi)->symbol, eval(table, CAR(ai)));
    }

    value *res = eval(table, CAR(body));
    return res;
}


symbol *sym_set(symbol *table, char *name, value *v) {
    symbol *s = sym_lookup(table, name);        
    if(s) {
        s->v = v;
    } else {
        s = symbol_alloc();
        s->lifetime = t_dynamic;
        s->name = name;
        s->v = v;
        symbol_last->next = s;
    }
    return s;
}

symbol *sym_unset(symbol *table, char *name) {
    symbol *sn;
    for (symbol *s = table; s->next != SYMBOL_END; s = s->next) {
        if(!strcmp(s->next->name, name)) {
            sn = s->next;
            s->next = s->next->next;
            return sn;
        }
    }

    return SYMBOL_END;
}

void print_symtable(symbol *table) {
    for (symbol *s = table; s != SYMBOL_END; s = s->next) {
        printf("%s : ", s->name);
        print_value(s->v);
        printf("\n");
    }
}
