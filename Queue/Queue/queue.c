#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

typedef struct QueueElement {
    int value;
    struct QueueElement* previous;
} QueueElement;

struct Queue {
    QueueElement * front;
    QueueElement * back;
};

void Dequeue(Queue* queue) {
    QueueElement* tmp = queue->front;
    queue->front = queue->front->previous;
    free(tmp);
}

/*Stack* createStack() {
    return (Stack*)calloc(1, sizeof(Stack));
*/

void Enqueue(Queue* queue, int value) {
    QueueElement* element = malloc(sizeof(QueueElement));
    assert(element != NULL);
    element->previous = NULL;
    element->value = value;
    queue->back->previous = element;
    queue->back = element;
}