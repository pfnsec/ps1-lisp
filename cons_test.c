#include "cons.h"
#include "symtable.h"
#include "cache.h"
#include <stdio.h>

value test = CONS( 
   SYMBOL("*"),
   CONS(
    SYMBOL("2"), 
    CONS(
        CONS(
            SYMBOL("+"), 
            CONS(
                SYMBOL("3"), 
                CONS(
                    SYMBOL("4"), 
                    NIL))), 
        NIL))
);

value v = CONS(SYMBOL("define"), CONS(CONS(SYMBOL("sqrt"), CONS(SYMBOL("x"), CONS(SYMBOL("y"), NIL))), CONS(CONS(SYMBOL("*"), CONS(SYMBOL("x"), CONS(SYMBOL("y"), NIL))), NIL)));

defun times_ten(value *v) {
    v->word += 1;
    return v;
}

value fnt = {
    .type = t_defun,
    .fn = times_ten
};

symbol *sym_table = 
            SYMBOL_ENTRY("test", &v,
            SYMBOL_ENTRY("times_ten", &fnt,
            SYMBOL_ENTRY("toast", &test, 
            SYMBOL_ENTRY("teest", &v, SYMBOL_END))));

cons hund = {
    .car = SYMBOL("times_ten"), 
    .cdr = CONS(SYMBOL("times_ten"), WORD(10))
};



void print_cons(cons *c);

void print_value(value *v) {
    if(v->type == t_nil) {
        printf("()");
    } else if(v->type == t_symbol) {
        printf("%s", v->symbol);
    } else if(v->type == t_word) {
        printf("%x", v->word);
    } else if(v->type == t_cons) {
        print_cons(v->cons);
    }

    printf(" ");
}

void print_cons(cons *c) {
    printf("(");
    print_value(&c->car);
    print_value(&c->cdr);
    printf(")");
    
}

int main() {
    cons *c = cons_alloc();
    cons_free(cons_alloc());
    cons_free(cons_alloc());
    cons_free(cons_alloc());
    cons_free(cons_alloc());
    cons_free(cons_alloc());
    cons_free(c);
    print_value(eval(sym_table, &hund));
    print_value(sym_lookup(sym_table, "test"));
    printf("\n");
    print_value(sym_lookup(sym_table, "toast"));
    printf("\n");
    return 0;
}
