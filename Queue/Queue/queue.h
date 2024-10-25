#pragma once

typedef struct Queue Queue;

void enqueue(Queue * queue, int value);

void dequeue(Queue* queue);

Queue* createQueue();
