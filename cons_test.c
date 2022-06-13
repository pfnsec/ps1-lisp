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




value fact = CONS(SYMBOL("define"), CONS(SYMBOL("fact"), CONS(CONS(SYMBOL("lambda"), CONS(CONS(SYMBOL("x"), NIL), CONS(CONS(SYMBOL("if"), CONS(CONS(SYMBOL("="), CONS(SYMBOL("x"), CONS(WORD(1), NIL))), CONS(SYMBOL("x"), CONS(CONS(SYMBOL("*"), CONS(SYMBOL("x"), CONS(CONS(SYMBOL("fact"), CONS(CONS(SYMBOL("-"), CONS(SYMBOL("x"), CONS(WORD(1), NIL))), NIL)), NIL))), NIL)))), NIL))), NIL)));

value ten_fact = CONS(SYMBOL("fact"), CONS(WORD(10), NIL));

value is_three = CONS(SYMBOL("define"), CONS(SYMBOL("is-3"), CONS(CONS(SYMBOL("lambda"), CONS(CONS(SYMBOL("x"), NIL), CONS(CONS(SYMBOL("if"), CONS(CONS(SYMBOL("="), CONS(SYMBOL("x"), CONS(WORD(3), NIL))), CONS(WORD(1), CONS(WORD(0), NIL)))), NIL))), NIL)));

value map_three = CONS(SYMBOL("map"), CONS(SYMBOL("is-3"), CONS(CONS(WORD(3), CONS(WORD(4), CONS(WORD(3), CONS(WORD(2), NIL)))), NIL)));

value test_map = CONS(SYMBOL("map"), CONS(CONS(SYMBOL("lambda"), CONS(CONS(SYMBOL("x"), NIL), CONS(CONS(SYMBOL("*"), CONS(WORD(10), CONS(SYMBOL("x"), NIL))), NIL))), CONS(CONS(WORD(1), CONS(WORD(2), CONS(WORD(3), CONS(WORD(4), CONS(WORD(5), NIL))))), NIL)));

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
    } else if(v->type == t_lambda) {
        printf("lambda ");
        print_cons(v->cons);
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
    /*
    print_value(eval(prelude_symtable, &is_three));
    printf("\n");
    print_value(eval(prelude_symtable, &map_three));
    printf("\n");


    print_value( &test_map);
    printf("\n");
    print_value(eval(prelude_symtable, &test_map));
    printf("\n");

    */
    print_value(eval(prelude_symtable, &fact));
    printf("\n");
    print_value(eval(prelude_symtable, &ten_fact));
    printf("\n");

    print_symtable(prelude_symtable);
    printf("\n");
   
    mark_reset();
    mark(prelude_symtable);
    sweep();
    printf("\n");
    return 0;
}
