CFLAGS=-Wall -Werror -pedantic -std=gnu99

test-power: test-power.o power.o
	gcc -o test-power test-power.o power.o

test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c

power.o: power.c
	gcc $(CFLAGS) -c power.c

.PHONY: clean
clean:
	rm -f *~ test-power *.o
