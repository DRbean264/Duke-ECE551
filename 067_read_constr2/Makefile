CPPFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3
code: code.o
	g++ -ggdb3 -o code code.o
code.o: code.cpp
	g++ $(CPPFLAGS) -c code.cpp

.PHONY: clean
clean:
	rm -f *~ code code.o
