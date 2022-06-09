
#include <stdio.h>
#include "cache.h"

ccache_block ccache_start = CCACHE_BLOCK(CCACHE_BLOCK_END);
vcache_block vcache_start = VCACHE_BLOCK(VCACHE_BLOCK_END);

// todo: store a cache_block * here and set it up as the 'most recently allocated'
// block, in order to take advantage of temporal locality 


cons *cons_alloc() {
    ccache_block *b = &ccache_start;

    while(b != CCACHE_BLOCK_END) {
        int n = __builtin_ffsl(~b->mask);
        printf("%x, ffs = %d\n", b->mask, n);
        if(n == 0) {
            b = b->next;
        } else {
            printf("alloc mask: %x ->", b->mask);
            b->mask |= (1 << (n - 1));
            printf("%x\n", b->mask);
            return &b->block[n - 1];
        }
    }
    printf("alloc failed :( \n");

    // You lose! You get nothing!
    return (cons *)0;
}

void cons_free(cons *c) {
    ccache_block *b = &ccache_start;

    while(b != CCACHE_BLOCK_END) {
        if((c < b->block) || c > b->block + CCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            printf("free mask: %x ->", b->mask);
            b->mask &= ~(1 << CCACHE_BLOCK_INDEX(b->block, c));
            printf("%x\n", b->mask);
            return;
        }
    }
    printf("free failed :(\n");
}

value *value_alloc() {
    vcache_block *b = &vcache_start;

    while(b != VCACHE_BLOCK_END) {
        int n = __builtin_ffsl(~b->mask);
        printf("%x, ffs = %d\n", b->mask, n);
        if(n == 0) {
            b = b->next;
        } else {
            printf("alloc mask: %x ->", b->mask);
            b->mask |= (1 << (n - 1));
            printf("%x\n", b->mask);
            return &b->block[n - 1];
        }
    }
    printf("alloc failed :( \n");

    // You lose! You get nothing!
    return (cons *)0;
}

void value_free(value *v) {
    vcache_block *b = &vcache_start;

    while(b != VCACHE_BLOCK_END) {
        if((v < b->block) || v > b->block + VCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            printf("free mask: %x ->", b->mask);
            b->mask &= ~(1 << VCACHE_BLOCK_INDEX(b->block, v));
            printf("%x\n", b->mask);
            return;
        }
    }
    printf("free failed :(\n");
}
