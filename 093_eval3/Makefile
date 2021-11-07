CPPFLAGS = -Wall -Werror -pedantic -std=gnu++98 -ggdb3

cyoa-step1: cyoa-step1.o
	g++ $(CPPFLAGS) -o cyoa-step1 cyoa-step1.o

cyoa-step1.o: cyoa-step1.cpp page.h
	g++ $(CPPFLAGS) -c cyoa-step1.cpp page.h

.PHONY: clean
clean:
	rm -f *~ *.o cyoa-step1
