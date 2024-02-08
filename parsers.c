#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
int parse_num(char* string){
    long lout = strtol(string,NULL,10);
    if (errno == ERANGE || lout > INT_MAX){
        printf("Encountered an error: Number:\"%s\" is to big to fit into an integer\nThe program will terminate",string);
        exit(EXIT_FAILURE);
    }

    return (int) lout;
}