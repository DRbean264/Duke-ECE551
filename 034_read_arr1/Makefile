test: test.o
	gcc -o test test.o
test.o: test.c
	gcc -Wall -Werror -pedantic -std=gnu99 -c test.c

.PHONY: clean
clean:
	rm -f *~ test *.o
