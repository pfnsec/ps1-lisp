#ifndef CONS_H
#define CONS_H

#include <stdint.h>

typedef struct value value;
typedef struct cons cons;

// Define a function type defun, taking a datum and returning a datum.
typedef struct value *(*defun)(value *v);

typedef struct value {
  enum type { 
      t_cons, 
      t_symbol, 
      t_word, 
      t_defun, 
      t_lambda, 
      t_nil
  } type;

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

#define IS_NIL(__value)   (__value->type == t_nil)
#define IS_CONS(__value)  (__value->type == t_cons)
#define IS_LAMBDA(__value)  (__value->type == t_lambda)
#define IS_WORD(__value)  (__value->type == t_word)
#define IS_DEFUN(__value) (__value->type == t_defun)
#define IS_SYMBOL(__value) (__value->type == t_symbol)

#define CAR(__value) ((value *)(&__value->cons->car))
#define CDR(__value) ((value *)(&__value->cons->cdr))

#define CAAR(__value) CAR(CAR(__value))
#define CADR(__value) CAR(CDR(__value))
#define CDDR(__value) CDR(CDR(__value))
#define CDAR(__value) CDR(CAR(__value))

#define CONS_ITER(__vi, __value) for(value *__vi = __value; !IS_NIL(__vi); __vi = CDR(__vi))

void print_cons(cons *c);

void print_value(value *v);

#endif
