all: clean main.o parsers.o
	clang main.o parsers.o -o ttable -Wall -Wextra -g

main.o: main.c
	clang main.c -c -Wall -Wextra -g

parsers.o: parsers.c parsers.h
	clang parsers.c -c -Wall -Wextra -g

clean:
	rm -f *.o ttable