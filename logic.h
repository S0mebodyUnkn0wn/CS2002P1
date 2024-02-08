#ifndef W05_LOGIC_H
#define W05_LOGIC_H
#include <stdbool.h>

// Wrapper functions for logical operators.
// Mainly required to simplify writing implication and xor.
// Other functions added for consistency

/*
 * Convenience wrapper for logical not
 */
bool not(bool a);
/*
 * Convenience wrapper for logical and
 */
bool and(bool a,bool b);
/*
 * Convenience wrapper for logical or
 */
bool or (bool a, bool b);
/*
 * Convenience wrapper for logical xor
 */
bool xor (bool a, bool b);
/*
 * Convenience wrapper for logical implication
 */
bool impl (bool a, bool b);
/*
 * Convenience wrapper for logical equality
 */
bool eq (bool a, bool b);
#endif //W05_LOGIC_H
