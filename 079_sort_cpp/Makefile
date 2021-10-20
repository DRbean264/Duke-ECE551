CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
sortLines: sortLines.o
	g++ -o sortLines $(CCFLAGS) sortLines.o

%.o: sortLines.cpp
	g++ -c $(CCFLAGS) sortLines.cpp

clean:
	rm -f *.o  *~ sortLines
