CFLAGS = -Wall -Werror -pedantic -Wsign-compare -Wwrite-strings -Wtype-limits -std=gnu99 -ggdb3

test: test.o
	gcc -o test test.o
test.o: test.c
	gcc -c $(CFLAGS) test.c

.PHONY: clean
clean:
	rm -f *~ *.o test
