
all: cons_test.c symtable.c cache.c
	gcc -g -std=gnu11 cons_test.c cache.c symtable.c prelude.c -o cons_test

