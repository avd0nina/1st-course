#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *CreateStack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = 0;
    stack->data = (unsigned short *)malloc(sizeof(unsigned short) * size);
    return stack;
}

void DestroyStack(Stack *stack) {
    free(stack->data);
    free(stack);
}

void PushIntoStack(Stack *stack, unsigned short value) {
    stack->data[stack->size++] = value;
}

unsigned short PopStack(Stack *stack) {
    return stack->data[--stack->size];
}

void PrintStack(Stack *result) {
    while (result->size) {
        printf("%d ", PopStack(result));
    }
}
