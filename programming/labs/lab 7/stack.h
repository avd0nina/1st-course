#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int size;
    unsigned short *data;
} Stack;

Stack *CreateStack(int size);
void DestroyStack(Stack *stack);
void PushIntoStack(Stack *stack, unsigned short value);
unsigned short PopStack(Stack *stack);
void PrintStack(Stack *result);

#endif // STACK_H 
