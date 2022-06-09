#ifndef CACHE_H
#define CACHE_H

#include "cons.h"

#include <stdint.h>

#define CCACHE_BLOCK_BYTES (32 * sizeof(cons))
#define CCACHE_BLOCK_INDEX(block, c) ((c - block) / sizeof(cons))

#define VCACHE_BLOCK_BYTES (32 * sizeof(cons))
#define VCACHE_BLOCK_INDEX(block, v) ((v - block) / sizeof(value))

typedef struct ccache_block {
    uint32_t mask;
    cons block[32];
    struct ccache_block *next;
} ccache_block;

typedef struct vcache_block {
    uint32_t mask;
    value block[32];
    struct vcache_block *next;
} vcache_block;

#define CCACHE_BLOCK(__next) { .mask = 0, .block = { [0 ... 31] = {.car = WORD(0), .cdr = WORD(0)}}, .next = __next }
#define CCACHE_BLOCK_END (ccache_block *)0

#define VCACHE_BLOCK(__next) { .mask = 0, .block = { [0 ... 31] = {.type = t_nil}}, .next = __next }
#define VCACHE_BLOCK_END (vcache_block *)0

cons *cons_alloc();
void cons_free(cons *c);
void cons_free_rec(cons *c);

value *value_alloc();
void value_free(value *v);
void value_free_rec(value *v);

#endif
