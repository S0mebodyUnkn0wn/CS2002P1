#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parsers.h"
#define MAX_VARS 26



int main(int argc, char *argv[]) {
    if (argc != 3){ // expect 3 arguments, because argv[0] is path to the executable
        printf("Unexpected number of arguments supplied (%d instead of 2)\n",argc-1);
        return 1;
    }
    int var_count = parse_num(argv[1]);
    if (var_count>MAX_VARS){
        printf("The program cannot process more than 26 variables.\nThe program will terminate\n");
        exit(EXIT_FAILURE);
    }

    //printf(formula);
    return 0;
}
