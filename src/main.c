#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "parsers.h"
#include "constants.h"
#include "stack.h"

/*
 * Break int vars into bits, and print them
 */
void print_bits(int var_count, int vars) {
    BoolStack bits = createBStack(); // Since we have already implemented the stack, might as well use it here
    for (int i = 0; i < var_count; i++) {
        push(&bits, vars % 2); // Push last bit of vars into the stack (or just 0 if vars has run out of bits)
        vars >>= 1; // RShift the stack, thus making second to last bit the last bit
    }
    while (bits.size > 0) {
        printf("%d ", pop(&bits)); // Since we used a stack the order of bits get reversed (exactly what we want)
    }
    printf(": "); // Print a vertical separator
}

/*
 * Print a line of formula's intermediate and final results for given vars
 */
void print_for_vars(int var_count, int vars, char *formula) {
    BoolStack buffer = createBStack();// <- a bool buffer, stores evaluated, but not yet consumed values,
    // should be reduced to len of 1 after the function has been processed
    int i = 0; // <- char index

    char currentChar = formula[i]; // <- char to be processed. Each char evaluates to a value, which is pushed onto buffer

    // Print var values used for this line
    print_bits(var_count, vars);

    do {
        bool val; // <- this operation's value

        // Evaluate val based on the character, also print the result of the application (unless a literal or var)
        if isalpha(currentChar) {            // Char is a var
                                                // evaluates to the var value, defined by int vars
            val = ((vars & (1 << (('a' + var_count - 1) - currentChar))) > 0);
            printf(" ");
        } else if isdigit(currentChar) {     // Char is a literal
            val = currentChar == '1';           // evaluates to itself
            printf(" ");
        } else if (currentChar == '-') {     // Char is a negation operator
            val = !pop(&buffer);          //  evaluates to negative of the last value
            printf("%d", val);
        } else {                             // Char is a compound operator
            bool b = pop(&buffer);        // evaluates to the result of the operator application on last two values
            bool a = pop(&buffer);
            val = eval_compound(a, b, currentChar);
            printf("%d", val);
        }

        // Place val into buffer to be consumed later
        push(&buffer, val);
        currentChar = formula[++i];
    } while (currentChar != 0); // Exit the loop when we get to the null char (End of the string)

    // if buf is not reduced to size of 1, the formula is not formed correctly, return an error
    if (buffer.size != 1) {
        printf("Could not parse the formula");
        exit(EXIT_FAILURE);
    }
    // Print the result
    printf(" :   %d\n", peek(&buffer));
}

/*
 * Prints a header for the truth table
 */
void print_header(int var_count, char *string) {
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

/*
 * The main function
 */
int main(int argc, char *argv[]) {
    // Verify arg count
    if (argc != 3) { // expect 3 arguments, because argv[0] is path to the executable
        printf("Unexpected number of arguments supplied (%d instead of 2)\n", argc - 1);
        return 1;
    }
    int var_count = parse_num(argv[1]);
    // Verify var_count is in bounds
    if (var_count > MAX_VARS) {
        printf("The program cannot process more than 26 variables.\nThe program will terminate\n");
        exit(EXIT_FAILURE);
    }
    if (var_count < 1) {
        printf("The program requires for at least one variable to be present in the formula.\nThe program will terminate");
        exit(EXIT_FAILURE);
    }
    // Verify that the formula is shorter than 1000 chars
    if (strlen(argv[2]) > 1000) {
        printf("Maximum input length (1000 chars) exceeded\nThe program will terminate\n");
        exit(EXIT_FAILURE);
    }
    // Build the table
    print_header(var_count, argv[2]);
    for (int i = 0; i < 1 << (var_count); i++) {
        // We can use binary interpretation of "i" as values for the formula's variables,
        // Since "i" will go through all possible combinations
        print_for_vars(var_count, i, argv[2]);
    }

    // If we got here, the program has successfully printed the table, yay!
    return 0;
}


