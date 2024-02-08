all: ../main.o parsers.o logic.o stack.o
	rm -f ttable
	clang main.o parsers.o logic.o stack.o -o ttable -Wall -Wextra -g

main.o: main.c
	rm -f main.o
	clang main.c -c -Wall -Wextra -g

parsers.o: parsers.c parsers.h
	rm -f parsers.o
	clang parsers.c -c -Wall -Wextra -g

logic.o: logic.c logic.h
	rm -f logic.o
	clang logic.c -c -Wall -Wextra -g

stack.o: stack.c stack.h
	rm -f stack.o
	clang stack.c -c -Wall -Wextra -g

clean:
	rm -f *.o ttable