#ifndef CONS_H
#define CONS_H

#include <stdint.h>

typedef struct value value;
typedef struct cons cons;

// Define a function type defun, taking a datum and returning a datum.
typedef struct value *(*defun)(value *v);

typedef struct value {
  enum type { t_cons, t_symbol, t_word, t_defun, t_nil} type;

  union {
    cons     *cons;
    uint32_t  word;
    char     *symbol;
    defun     fn;
  };
} value;


typedef struct cons {
    value car, cdr;
} cons;


#define SYMBOL(__symbol) { .type = t_symbol, .symbol = __symbol }
#define WORD(__word)     { .type = t_word,   .word = __word }
#define NIL { .type = t_nil }
#define CONS(__car, __cdr) { .type = t_cons, .cons = &(cons){ .car = __car, .cdr = __cdr } }
#define DEFUN(__fn)      { .type = t_defun,  .fn = __fn }


#endif
