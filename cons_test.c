#include "cons.h"
#include "symtable.h"
#include "cache.h"
#include "prelude.h"
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

value *map(value *v) {
    return v;
}

value *times_ten(value *v) {
    v->word += 1;
    return v;
}

value map_v = {
    .type = t_defun,
    .fn = map
};

value fnt = {
    .type = t_defun,
    .fn = times_ten
};

symbol *sym_table = 
            SYMBOL_ENTRY("test", &v,
            SYMBOL_ENTRY("map", &map_v,
            SYMBOL_ENTRY("times_ten", &fnt,
            SYMBOL_ENTRY("toast", &test, 
            SYMBOL_ENTRY("teest", &v, SYMBOL_END)))));

value hund = CONS(
    SYMBOL("map"), 
    CONS(SYMBOL("times_ten"), CONS(WORD(1), CONS(WORD(2), NIL)))
    );



value twelve = CONS(SYMBOL("*"), CONS(WORD(3), CONS(WORD(3), CONS(WORD(3), CONS(WORD(3), NIL)))));


value fact = CONS(SYMBOL("defun"), CONS(CONS(SYMBOL("fact"), CONS(SYMBOL("x"), NIL)), CONS(CONS(SYMBOL("if"), CONS(CONS(SYMBOL("="), CONS(SYMBOL("x"), CONS(SYMBOL("1"), NIL))), CONS(SYMBOL("x"), CONS(CONS(SYMBOL("*"), CONS(SYMBOL("x"), CONS(CONS(SYMBOL("fact"), CONS(CONS(SYMBOL("-"), CONS(SYMBOL("x"), CONS(SYMBOL("1"), NIL))), NIL)), NIL))), NIL)))), NIL)));



void print_value(value *v) {
    if(!v) {
        printf("#NULLPTR");
    } else if(v->type == t_nil) {
        printf("()");
    } else if(v->type == t_symbol) {
        printf("%s", v->symbol);
    } else if(v->type == t_word) {
        printf("%x", v->word);
    } else if(v->type == t_defun) {
        printf("<defun>");
    } else if(v->type == t_cons) {
        print_cons(v->cons);
    }

//    printf(" \n");
}

void print_cons(cons *c) {
    printf("(");
    print_value(&c->car);
    print_value(&c->cdr);
    printf(")");
    
}

int main() {
    // cons *c = cons_alloc();
    // cons_free(cons_alloc());
    // cons_free(cons_alloc());
    // cons_free(cons_alloc());
    // cons_free(cons_alloc());
    // cons_free(cons_alloc());
    // cons_free(c);
    mark_reset();
    print_value(&twelve);
    print_value(eval(prelude_symtable, &twelve));
    mark(prelude_symtable);
    sweep();
    printf("\n");
    return 0;
}
