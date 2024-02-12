#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsers.h"
#include "constants.h"
#include "printers.h"


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
        printf("The program requires for at least one variable to be present in the formula.\nThe program will terminate\n");
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


