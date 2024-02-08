
// Stack operations
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

BoolStack createBStack(){
    BoolStack new_stack;
    new_stack.base = NULL;
    new_stack.size = 0;
    return new_stack;
}

bool peek(BoolStack *stack){
    return *(stack->base + stack->size - 1);
}

void push(BoolStack *stack, bool val){
    int size = stack->size;
    bool* new_pt;

    // Code below adapted from examples on https://en.cppreference.com/w/c/memory/realloc
    if ((new_pt = (bool*) realloc(stack->base, (size + 1) * sizeof(bool)))){
        stack->base = new_pt;
    } else {
        printf("Encountered an error while extending a stack, the program will terminate");
        exit(EXIT_FAILURE);
    }
    // End code adapted from https://en.cppreference.com/w/c/memory/realloc

    *(stack->base + size) = val;
    stack->size++;
}

bool pop(BoolStack *stack){
    int size = stack->size;
    if (size<=0){
        return 0;
    }
    bool val = peek(stack);
    // Since calling realloc with 0 size causes undefined (implementation-defined before C23) behaviour (see https://en.cppreference.com/w/c/memory/realloc),
    // handle this case separately.
    if (size==1){
        stack->base = NULL;
        stack->size = 0;
        return val;
    }

    bool* new_pt;
    // Code below adapted from examples on https://en.cppreference.com/w/c/memory/realloc
    if ((new_pt = (bool*) realloc(stack->base, (size - 1) * sizeof(bool)))){
        stack->base = new_pt;
    } else {
        printf("Encountered an error while shrinking a stack, the program will terminate");
        exit(EXIT_FAILURE);
    }
    // End code adapted from https://en.cppreference.com/w/c/memory/realloc

    stack->size--;
    return val;
}

