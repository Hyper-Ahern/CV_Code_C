CFLAGS=-std=c99 -g
LDFLAGS=-g

.PHONY: all clean

all: permutations stringset

clean:
	rm -f permutations permutations.o stringset stringset.o linked_list.o node_pool.o

permutations: permutations.o
	gcc -o $@ $(LDFLAGS) $^

permutations.o: permutations.c

stringset: stringset.o linked_list.o node_pool.o
	gcc -o $@ $(LDFLAGS) $^

stringset.o: stringset.c linked_list.h

linked_list.o: linked_list.c linked_list.h node_pool.h

node_pool.o: node_pool.c node_pool.h

%.o:
	gcc -c $(CFLAGS) $<
