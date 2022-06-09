
all: cons_test.c symtable.c cache.c
	gcc -std=gnu11 cons_test.c cache.c symtable.c -o cons_test

