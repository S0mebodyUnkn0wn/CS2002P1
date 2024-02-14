//
// Stack operations
//
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include "stack.h"
BoolStack createBStack(){ // Find function desc in stack.h
    BoolStack new_stack;
    new_stack.base = NULL;
    new_stack.size = 0;
    return new_stack;
}

bool peek(BoolStack *stack){ // Find function desc in stack.h
    return *(stack->base + stack->size - 1);
}

void push(BoolStack *stack, bool val){ // Find function desc in stack.h
    unsigned int size = stack->size;
    bool* new_pt;
    if (size == UINT_MAX){
        // We are about to overflow the size, let's not do that
        printf("\nError: stack size overflow, the program will terminate\n");
        destruct(stack);
        exit(EXIT_FAILURE);
    }
    // Code below adapted from examples on https://en.cppreference.com/w/c/memory/realloc
    if ((new_pt = (bool*) realloc(stack->base, (size + 1) * sizeof(bool)))){
        stack->base = new_pt;
    } else { // if new_pt is a fasle (a NULL pointer) something went wrong and we should exit
        printf("\nEncountered an error while extending a stack, the program will terminate\n");
        free(stack->base); // cleanup
        exit(EXIT_FAILURE);
    }
    // End code adapted from https://en.cppreference.com/w/c/memory/realloc

    *(stack->base + size) = val;
    stack->size++;
}

bool pop(BoolStack *stack){ // Find function desc in stack.h
    unsigned int size = stack->size;
    if (size==0){
        printf("\nError: tried to retrieve an item from an empty stack, the program will terminate\n");
        destruct(stack); // free the stack
        exit(EXIT_FAILURE);
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
        printf("\nEncountered an error while shrinking a stack, the program will terminate\n");
        destruct(stack); // free the stack
        exit(EXIT_FAILURE);
    }
    // End code adapted from https://en.cppreference.com/w/c/memory/realloc

    stack->size--;
    return val;
}

void destruct(BoolStack *stack){
    free(stack->base);
    stack->size = 0;
}

