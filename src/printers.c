//
// Functions that print things into console
//
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"
#include "parsers.h"

void print_bits(int var_count, int vars) {// Find function desc in printers.h
    BoolStack bits = createBStack(); // Since we have already implemented the stack, might as well use it here
    for (int i = 0; i < var_count; i++) {
        push(&bits, vars % 2); // Push last bit of vars into the stack (or just 0 if vars has run out of bits)
        vars >>= 1; // RShift the stack, thus making second to last bit the last bit
    }
    while (bits.size > 0) {
        printf("%d ", pop(&bits)); // Since we used a stack the order of bits get reversed (exactly what we want)
    }
    printf(": "); // Print a vertical separator
    destruct(&bits); // free memory allocated to bits (redundancy measure, memory should already be free at this point)
}


void print_for_vars(int var_count, int vars, char *formula) {// Find function desc in printers.h
    BoolStack buffer = createBStack();// <- a bool buffer, stores evaluated, but not yet consumed values,
    // should be reduced to len of 1 after the function has been processed
    int i = 0; // <- char index

    char currentChar = formula[i]; // <- char to be processed. Each char evaluates to a value, which is pushed onto buffer

    // Print var values used for this line
    print_bits(var_count, vars);

    do {
        bool val; // <- this operation's value

        // Evaluate val based on the character, also print the result of the application (unless a literal or var)
        if (isalpha(currentChar)&& islower(currentChar)) {
                                             // Char is a var
                                                // evaluates to the var value, defined by int vars
            int var_index = ('a' + var_count - 1) - currentChar;
            if (var_index>=var_count || var_index < 0){
                printf("\nEncountered an error while processing a variable:\n"
                              "    could not parse variable: '%c'\n"
                              "The program will terminate\n",currentChar);
                destruct(&buffer);
                exit(EXIT_FAILURE);
            }
            val = ((vars & (1 << (var_index))) > 0);
            printf(" ");
        } else if (currentChar=='1' || currentChar=='0') {     // Char is a literal
            val = currentChar == '1';           // evaluates to itself
            printf(" ");
        } else if (currentChar == '-') {     // Char is a negation operator
            val = !pop(&buffer);          //  evaluates to negative of the last value
            printf("%d", val);
        } else {                             // Char is a compound operator
            bool b = pop(&buffer);        // evaluates to the result of the operator application on last two values
            bool a = pop(&buffer);
            int res = eval_compound(a, b, currentChar);
            if (res == -1){ // If -1 is returned - eval_compound couldn't parse the char
                printf("\nEncountered an error while processing an operator:"
                       "\n    Could not parse '%c'"
                       "\nThe program will terminate\n", currentChar);
                destruct(&buffer);
                exit(EXIT_FAILURE);
            }
            val = (bool) res;
            printf("%d", val);
        }

        // Place val into buffer to be consumed later
        push(&buffer, val);
        currentChar = formula[++i];
    } while (currentChar != 0); // Exit the loop when we get to the null char (End of the string)

    // if buf is not reduced to size of 1, the formula is not formed correctly, return an error
    if (buffer.size != 1) {
        printf("\nCould solve the formula, likely not enough operators were supplied\nThe program will terminate\n");
        destruct(&buffer); // Free whatever is left in the buffer
        exit(EXIT_FAILURE);
    }
    // Print the result
    printf(" :   %d\n", peek(&buffer));
    destruct(&buffer); // Free whatever is left in the buffer
}


void print_header(int var_count, char *string) {// Find function desc in printers.h
    int total_len = 0; // <- length of the header, used to draw appropriately sized separator
    for (int i = 'a'; i < var_count + 'a'; i++) {
        total_len += printf("%c ", i); // Print vars
    }
    total_len += printf(": %s : Result\n", string); // print the formula
    for (int i = 0; i < total_len -
                        1; i++) { // Print the separator of length total_len - 1 ( -1 is for the \n, which is not visible)
        printf("=");
    }
    printf("\n");
}