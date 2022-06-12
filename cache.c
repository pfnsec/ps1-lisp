
#include <stdio.h>
#include "cache.h"

ccache_block ccache_start = CCACHE_BLOCK(CCACHE_BLOCK_END);
ccache_block *ccache_latest = &ccache_start;

vcache_block vcache_start = VCACHE_BLOCK(VCACHE_BLOCK_END);
vcache_block *vcache_latest = &vcache_start;

symcache_block symcache_start = SYMCACHE_BLOCK(SYMCACHE_BLOCK_END);
symcache_block *symcache_latest = &symcache_start;


cons *cons_alloc() {
    ccache_block *b = &ccache_start;

    while(b != CCACHE_BLOCK_END) {
        int n = __builtin_ffsl(~b->mask);
        if(n == 0) {
            b = b->next;
        } else {
            b->mask |= (1 << (n - 1));
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
            b->mask &= ~(1 << CCACHE_BLOCK_INDEX(b->block, c));
            return;
        }
    }
    printf("free failed :(\n");
}

value *value_alloc() {
    vcache_block *b = &vcache_start;

    while(b != VCACHE_BLOCK_END) {
        int n = __builtin_ffsl(~b->mask);
        if(n == 0) {
            b = b->next;
        } else {
            b->mask |= (1 << (n - 1));
            return &b->block[n - 1];
        }
    }
    printf("alloc failed :( \n");

    // You lose! You get nothing!
    return (value *)0;
}

void value_free(value *v) {
    vcache_block *b = &vcache_start;

    while(b != VCACHE_BLOCK_END) {
        if((v < b->block) || v > b->block + VCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            b->mask &= ~(1 << VCACHE_BLOCK_INDEX(b->block, v));
            return;
        }
    }
    printf("free failed :(\n");
}

symbol *symbol_alloc() {
    symcache_block *b = &symcache_start;

    while(b != SYMCACHE_BLOCK_END) {
        int n = __builtin_ffsl(~b->mask);
        if(n == 0) {
            b = b->next;
        } else {
            b->mask |= (1 << (n - 1));
            return &b->block[n - 1];
        }
    }
    printf("alloc failed :( \n");

    // You lose! You get nothing!
    return (symbol *)0;
}

void symbol_free(symbol *s) {
    symcache_block *b = &symcache_start;

    while(b != SYMCACHE_BLOCK_END) {
        if((s < b->block) || s > b->block + SYMCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            b->mask &= ~(1 << SYMCACHE_BLOCK_INDEX(b->block, s));
            return;
        }
    }
    printf("free failed :(\n");
}

void mark_reset() {
    for(symcache_block *s = &symcache_start; s != SYMCACHE_BLOCK_END; s = s->next) {
        s->mark = 0;
    }

    for(ccache_block *c = &ccache_start; c != CCACHE_BLOCK_END; c = c->next) {
        c->mark = 0;
    }

    for(vcache_block *v = &vcache_start; v != VCACHE_BLOCK_END; v = v->next) {
        v->mark = 0;
    }

}

void mark_cons(cons *c) {
    ccache_block *b = &ccache_start;

    while(b != CCACHE_BLOCK_END) {
        if((c < b->block) || c > b->block + CCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            printf("mark: %x ->", b->mark);
            b->mark |= (1 << CCACHE_BLOCK_INDEX(b->block, c));
            printf("%x\n", b->mark);
            return;
        }
    }
}

void mark_value(value *v) {
    vcache_block *b = &vcache_start;

    while(b != VCACHE_BLOCK_END) {
        if((v < b->block) || v > b->block + VCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            printf("mark: %x ->", b->mark);
            b->mark |= (1 << VCACHE_BLOCK_INDEX(b->block, v));
            printf("%x\n", b->mark);
            return;
        }
    }
}

void mark_symbol(symbol *s) {
    symcache_block *b = &symcache_start;

    while(b != SYMCACHE_BLOCK_END) {
        if((s < b->block) || s > b->block + SYMCACHE_BLOCK_BYTES) {
            b = b->next;
        } else {
            printf("mark: %x ->", b->mark);
            b->mark |= (1 << SYMCACHE_BLOCK_INDEX(b->block, s));
            printf("%x\n", b->mark);
            return;
        }
    }
}

void mark_recurse(value *v) {
    printf("mark_recurse");
    mark_value(v);
    if(IS_CONS(v)) {
        mark_cons(v->cons);
        mark_recurse(CAR(v));
        mark_recurse(CDR(v));
    }
}

void mark(symbol *table) {
    for(symbol *s = table; s != SYMBOL_END; s = s->next) {
        if(s->lifetime == t_static) {
            continue;
        } else {
            mark_recurse(s->v);
        }
    }
}

void sweep() {
    for(symcache_block *s = &symcache_start; s != SYMCACHE_BLOCK_END; s = s->next) {
        printf("sym: mask %x, mark %x\n", s->mask, s->mark);
        s->mask = s->mark;
    }

    for(ccache_block *c = &ccache_start; c != CCACHE_BLOCK_END; c = c->next) {
        printf("cons: mask %x, mark %x\n", c->mask, c->mark);
        c->mask = c->mark;
    }

    for(vcache_block *v = &vcache_start; v != VCACHE_BLOCK_END; v = v->next) {
        printf("value: mask %x, mark %x\n", v->mask, v->mark);
        v->mask = v->mark;
    }
}
