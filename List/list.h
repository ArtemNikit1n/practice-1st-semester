#pragma once

typedef struct List List;

typedef ListElement * Position;

void deleteList(List ** list);

List * createList();

void add(List * list, Position position, int value);

