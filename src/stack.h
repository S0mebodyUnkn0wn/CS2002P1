#ifndef W05_STACK_H
#define W05_STACK_H

#include <stdbool.h>
#include "constants.h"

/* A stack of boolean values
 *
 * Direct interaction with BoolStack's fields is not recommend,
 * use functions from stack.h instead
 */
typedef struct BoolStack {
    bool *base; // pointer to the base of the stack (the lowest element)
    unsigned int size; // size of the stack. The top value of the stack is always located at (base+size-1)
} BoolStack;

/*
 * Initialise BoolStack
 */
BoolStack createBStack();

/*
 * Returns the top of the stack, doesn't modify the stack
 */
bool peek(BoolStack *stack);

/*
 * Removes the top element from the stack and returns it
 */
bool pop(BoolStack *stack);

/*
 * Puts a boolean value onto the stack
 */
void push(BoolStack *stack, bool val);

/*
 * Frees memory allocated to the stack
 */
void destruct(BoolStack *stack);
#endif //W05_STACK_H