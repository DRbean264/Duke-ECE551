CPPFLAGS = -Wall -Werror -pedantic -std=gnu++98 -ggdb3

cyoa-step2: cyoa-step2.o
	g++ $(CPPFLAGS) -o cyoa-step2 cyoa-step2.o

cyoa-step1: cyoa-step1.o
	g++ $(CPPFLAGS) -o cyoa-step1 cyoa-step1.o

cyoa-step1.o: cyoa-step1.cpp page.h utils.h
	g++ $(CPPFLAGS) -c cyoa-step1.cpp page.h utils.h

cyoa-step2.o: cyoa-step2.cpp page.h utils.h story.h
	g++ $(CPPFLAGS) -c cyoa-step2.cpp page.h utils.h story.h

.PHONY: clean
clean:
	rm -f *~ *.o cyoa-step2
