CPPFLAGS = -Wall -Werror -pedantic -ggdb3 -std=gnu++98
test-bsearch: search.o test-bsearch.o
	g++ $(CPPFLAGS) -o test-bsearch search.o test-bsearch.o

search.o: search.cpp function.h
	g++ $(CPPFLAGS) -c search.cpp function.h

test-bsearch.o: test-bsearch.cpp function.h
	g++ $(CPPFLAGS) -c test-bsearch.cpp function.h

.PHONY: clean
clean:
	rm -f *~ *.o test-bsearch
