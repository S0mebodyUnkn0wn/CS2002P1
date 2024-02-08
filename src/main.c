#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "parsers.h"
#include "logic.h"
#include "constants.h"
#include "stack.h"


bool eval_compound(bool a, bool b, char operator){
    switch (operator) {
        case '-' :
            return not(a);
        case '|':
            return or(a, b);
        case '&':
            return and(a, b);
        case '#':
            return xor(a, b);
        case '>':
            return impl(a, b);
        case '=':
            return eq(a, b);
        default:
            printf("Encountered an error while processing an operator:"
                   "\nCould not parse '%c'"
                   "\nThe program will terminate\n", operator);
            exit(EXIT_FAILURE);
    }
}

void print_bits(int var_count, int vars) {
    BoolStack bits = createBStack(); // Since we have already implemented the stack, might as well use it here
    for (int i=0; i<var_count;i++){
        push(&bits,vars%2);
        vars>>=1;
    }
    while (bits.size>0){
        printf("%d ",pop(&bits));
    }
    printf(": ");
}

void solve_for_vars(int var_count, int vars, char* formula){
    BoolStack buffer = createBStack();
    int i = 0; // index
    char currentChar = formula[i];
    print_bits(var_count,vars);
    do{
        bool val;
        if isalpha(currentChar){
            // Gets the number of a bit that would contain the value of n-th variable
            // Then bit ands that number with vars
            // If vars has a 0 in that bit - the result will be 0
            // If vars has a 1 in that bit - the result will be > 0
            val = ((vars & (1<<(('a'+var_count-1)-currentChar))) > 0);
            printf(" ");
        }
        else if isdigit(currentChar){
            val = currentChar=='1';
            printf(" ");
        }
        else if (currentChar=='-'){
            val = not(pop(&buffer));
            printf("%d",val);
        } else{
            bool b = pop(&buffer);
            bool a = pop(&buffer);
            val = eval_compound(a,b,currentChar);
            printf("%d",val);
        }
        push(&buffer,val);
        currentChar = formula[++i];
    } while (currentChar != 0);
    if (buffer.size!=1){
        printf("Could not parse the formula");
        exit(EXIT_FAILURE);
    }
    printf(" :   %d\n",peek(&buffer));
}

void print_header(int var_count, char *string) {
    int total_len = 0;
    for (int i = 'a'; i<var_count+'a';i++){
        total_len+=printf("%c ",i);
    }
    total_len+=printf(": %s : Result\n",string);
    for (int i = 0; i<total_len-1;i++){ // - 1 for the \n
        printf("=");
    }
    printf("\n");
}

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
    if (strlen(argv[2])>1000){
        printf("Maximum input length exceeded\nThe program will terminate\n");
        exit(EXIT_FAILURE);
    }
    print_header(var_count,argv[2]);
    for (int i = 0; i < 1<<(var_count);i++){
        solve_for_vars(var_count, i,argv[2]);
    }

    //printf(formula);
    return 0;
}


