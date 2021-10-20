CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
sortLines: sortLines.o
	g++ -o sortLines $(CCFLAGS) sortLines.o

sortLines.o: sortLines.cpp
	g++ -c $(CCFLAGS) sortLines.cpp

.PHONY: clean
clean:
	rm -f *.o *~ sortLines
