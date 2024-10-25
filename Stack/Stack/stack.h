#pragma once

typedef struct Stack Stack;

Stack* createStack();

void push(Stack* stack, int value);

void pop(Stack* stack);