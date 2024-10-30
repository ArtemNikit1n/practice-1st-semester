#pragma once

typedef struct List List;

void deleteList(List ** list);

List * createList();

void add(List* list, struct ListElement* position, int value);

void popList(List* list, struct ListElement* position, bool* errorCode);

