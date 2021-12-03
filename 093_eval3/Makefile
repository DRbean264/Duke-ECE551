CPPFLAGS = -Wall -Werror -pedantic -std=gnu++98 -ggdb3

cyoa-step4: cyoa-step4.o
	g++ $(CPPFLAGS) -o cyoa-step4 cyoa-step4.o

cyoa-step3: cyoa-step3.o
	g++ $(CPPFLAGS) -o cyoa-step3 cyoa-step3.o

cyoa-step2: cyoa-step2.o
	g++ $(CPPFLAGS) -o cyoa-step2 cyoa-step2.o

cyoa-step1: cyoa-step1.o
	g++ $(CPPFLAGS) -o cyoa-step1 cyoa-step1.o

cyoa-step1.o: cyoa-step1.cpp page.h utils.h
	g++ $(CPPFLAGS) -c cyoa-step1.cpp

cyoa-step2.o: cyoa-step2.cpp page.h utils.h story.h
	g++ $(CPPFLAGS) -c cyoa-step2.cpp

cyoa-step3.o: cyoa-step3.cpp page.h utils.h story.h
	g++ $(CPPFLAGS) -c cyoa-step3.cpp

cyoa-step4.o: cyoa-step4.cpp page.h utils.h story.h
	g++ $(CPPFLAGS) -c cyoa-step4.cpp

.PHONY: clean
clean:
	rm -f *~ *.o cyoa-step4 cyoa-step3 cyoa-step2 cyoa-step1 *.gch
