#ifndef CACHE_H
#define CACHE_H

#include "cons.h"
#include "symtable.h"

#include <stdint.h>

#define CCACHE_BLOCK_BYTES (32 * sizeof(cons))
#define CCACHE_BLOCK_INDEX(__block, __c) ((__c - __block) / sizeof(cons))

#define VCACHE_BLOCK_BYTES (32 * sizeof(value))
#define VCACHE_BLOCK_INDEX(__block, __v) ((__v - __block) / sizeof(value))

#define SYMCACHE_BLOCK_BYTES (32 * sizeof(symbol))
#define SYMCACHE_BLOCK_INDEX(__block, __s) ((__s - __block) / sizeof(symbol))

typedef struct ccache_block {
    uint32_t mask;
    uint32_t mark;
    cons block[32];
    struct ccache_block *next;
} ccache_block;

typedef struct vcache_block {
    uint32_t mask;
    uint32_t mark;
    value block[32];
    struct vcache_block *next;
} vcache_block;

typedef struct symcache_block {
    uint32_t mask;
    uint32_t mark;
    symbol block[32];
    struct symcache_block *next;
} symcache_block;

#define CCACHE_BLOCK(__next) { .mask = 0, .mark = 0, .block = { [0 ... 31] = {.car = WORD(0), .cdr = WORD(0)}}, .next = __next }
#define CCACHE_BLOCK_END (ccache_block *)0

#define VCACHE_BLOCK(__next) { .mask = 0, .mark = 0, .block = { [0 ... 31] = {.type = t_nil}}, .next = __next }
#define VCACHE_BLOCK_END (vcache_block *)0

#define SYMCACHE_BLOCK(__next) { .mask = 0, .mark = 0, .block = { [0 ... 31] = {.name = (char *)0, .lifetime = t_static, .v = (value *)0, .next = (symbol *)0 }}, .next = __next }
#define SYMCACHE_BLOCK_END (symcache_block *)0

cons *cons_alloc();
void cons_free(cons *c);
void cons_free_rec(cons *c);

value *value_alloc();
void value_free(value *v);
void value_free_rec(value *v);

symbol *symbol_alloc();
void symbol_free(symbol *s);
void symbol_free_rec(symbol *s);

void mark_reset();
void mark(symbol *table);
void sweep();




#endif
