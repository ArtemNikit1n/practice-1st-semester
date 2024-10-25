#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

typedef struct StackElement {
    int value;
    struct StackElement* next;
} StackElement;

struct Stack {
    StackElement* head;
};

void pop(Stack* stack) {
    StackElement* tmp = stack->head;
    stack->head = stack->head->next;
    free(tmp);
}

Stack* createStack() {
    return (Stack*)calloc(1, sizeof(Stack));
}

void push(Stack* stack, int value) {
    StackElement* element = malloc(sizeof(StackElement));
    assert(element != NULL);
    element->value = value;
    element->next = stack->head;
    stack->head = element;
}