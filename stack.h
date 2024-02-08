#ifndef W05_STACK_H
#define W05_STACK_H

#include <stdbool.h>
#include "constants.h"

typedef struct BoolStack {
    bool elems[MAX_VARS]; // Since the maximum number of values remembered in a stack
    int size;
} BoolStack;
void push(BoolStack stack);

#endif //W05_STACK_H