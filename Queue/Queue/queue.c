#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

typedef struct QueueElement {
    int value;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue {
    QueueElement* front; 
    QueueElement* back;  
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->back = NULL;
    return queue;
}

void enqueue(Queue* queue, int value) {
    QueueElement* element = (QueueElement*)malloc(sizeof(QueueElement));
    element->value = value;
    element->next = NULL;

    if (queue->back == NULL) {
        queue->front = queue->back = element;
    }
    else {

        queue->back->next = element;
        queue->back = element;
    }
}

void dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return;
    }

    QueueElement* tmp = queue->front;
    queue->front = queue->front->next;


    if (queue->front == NULL) {
        queue->back = NULL;
    }

    free(tmp);
}