#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef struct ListElement {
    int value;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* head;
};

List* createList(bool* errorCode) {
    ListElement* guardian = calloc(1, sizeof(ListElement));
    if (guardian == NULL) {
        *errorCode = true;
        return NULL;
    }
    List* list = calloc(1, sizeof(List));
    if (list == NULL) {
        *errorCode = true;
        return NULL;
    }
    list->head = guardian;
    return list;
}
