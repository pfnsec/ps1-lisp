#include "cons.h"
#include <stdio.h>

cons test = {
   .car = SYMBOL("*"),
   .cdr = CONS(
           SYMBOL("2"), 
           CONS(
               CONS(
                   SYMBOL("+"), 
                   CONS(
                       SYMBOL("3"), 
                       CONS(
                           SYMBOL("4"), 
                           NIL))), 
               NIL)),
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
    print_cons(&test);
    return 0;
}
