CPPFLAGS = -Wall -Werror -pedantic -ggdb3 -std=gnu++98
test: test.o
	g++ $(CPPFLAGS) -o test test.o

test.o: test.cpp bstmap.h
	g++ $(CPPFLAGS) -c test.cpp bstmap.h

.PHONY: clean
clean:
	rm -f *~ *.o test
