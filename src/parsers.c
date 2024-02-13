#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

// Define shorthands for logical operations. Equivalences taken from logic lecture 4
#define xor(X, Y) ((X) && !(Y)) || (!(X) && (Y))
#define impl(X, Y) (!(X) || (Y))

int eval_compound(bool a, bool b, char operator) { // Find function desc in parsers.h
    switch (operator) {
        case '|':
            return a || b;
        case '&':
            return a & b;
        case '#':
            return xor(a, b);
        case '>':
            return impl(a, b);
        case '=':
            return a == b;
        default:
            return -1;

    }
}

int parse_num(char* string){ // Find function desc in parsers.h
    long lout = strtol(string,NULL,10);
    if (errno == ERANGE || lout > INT_MAX){
        printf("Encountered an error while parsing a number:\n"
               "    Number: \"%s\" is to big to fit into an integer\n"
               "The program will terminate\n",string);
        exit(EXIT_FAILURE);
    }

    return (int) lout;
}