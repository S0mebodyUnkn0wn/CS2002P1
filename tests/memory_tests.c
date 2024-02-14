//
// Created by somebody on 13/02/24.
//
#include "../src/stack.h"
#include <stdio.h>

void stack_func(){
    BoolStack stack = createBStack();
    for (unsigned int i=0;i<1000000000;i++){
        push(&stack,true);
    }
    printf("pushed %u items into the stack while in a function\n",stack.size);
    scanf("%c");
    destruct(&stack);
}

int main(){
    BoolStack stack = createBStack();
    for (unsigned int i=0;i<2000000000;i++){
        push(&stack,true);
    }
    printf("pushed %u items into the stack\n",stack.size);
    scanf("%c");
    for (unsigned int i=0;i<2000000000;i++){
        pop(&stack);
    }
    printf("popped all items from the stack\n");
    scanf("%c");
    destruct(&stack);
    printf("destructed the long stack\n\n\n");

    stack_func();
    printf("destructed the stack and exited the function\n");
    scanf("%c");

}