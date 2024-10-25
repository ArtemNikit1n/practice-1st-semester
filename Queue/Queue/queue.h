#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#pragma once
typedef struct Queue Queue;
void enqueue(Queue * queue, int value);
void dequeue(Queue* queue);
Queue* createQueue();