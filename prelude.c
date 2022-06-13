#include "prelude.h"
#include "symtable.h"
#include "cons.h"
#include "cache.h"

value *_plus(value *v) {
    value *res = value_alloc();
    *res = (value)WORD(0);
    CONS_ITER(vi, v) {
        res->word += CAR(vi)->word;
    }
    return res;
}

value plus = {
    .type = t_defun,
    .fn = _plus
};

value *_minus(value *v) {
    value *res = value_alloc();
    *res = (value)WORD(0);
    res->word = CAR(v)->word - CADR(v)->word;
    return res;
}

value minus = {
    .type = t_defun,
    .fn = _minus
};

value *_eq(value *v) {
    value *res = value_alloc();
    *res = (value)WORD(0);
    if(CAR(v)->word == CADR(v)->word) {
        res->word = 1;
    }
    return res;
}

value eq = {
    .type = t_defun,
    .fn = _eq
};

value *_mul(value *v) {
    value *res = value_alloc();
    *res = (value)WORD(1);
    CONS_ITER(vi, v) {
        res->word *= CAR(vi)->word;
    }
    return res;
}

value mul = {
    .type = t_defun,
    .fn = _mul
};



symbol *prelude_symtable = 
            SYMBOL_ENTRY("=", &eq,
            SYMBOL_ENTRY("+", &plus,
            SYMBOL_ENTRY("-", &minus,
            SYMBOL_ENTRY("*", &mul,
            SYMBOL_END))));
