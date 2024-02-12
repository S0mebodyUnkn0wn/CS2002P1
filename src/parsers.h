#ifndef W05_PARSERS_H
#define W05_PARSERS_H
#include <stdbool.h>
/*
 * Convert a string into a number
 *
 * Terminates the program if integer overflow is detected
 */
int parse_num(char* string);

/*
 * Evaluates the result of "a" *operator* "b"
 *
 * Terminates the program if unable to parse the operator
 */
bool eval_compound(bool a, bool b, char operator);
#endif //W05_PARSERS_H
