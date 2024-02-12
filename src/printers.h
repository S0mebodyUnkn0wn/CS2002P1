
//

#ifndef W05_PRINTERS_H
#define W05_PRINTERS_H
/*
 * Break int vars into bits, and print them
 */
void print_bits(int var_count, int vars);
/*
 * Print a line of formula's intermediate and final results for given vars
 */
void print_for_vars(int var_count, int vars, char *formula);
/*
 * Prints a header for the truth table
 */
void print_header(int var_count, char *string);
#endif //W05_PRINTERS_H
