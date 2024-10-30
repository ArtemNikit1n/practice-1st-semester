struct List {
    ListElement* head;
};

typedef struct ListElement {
    int value;
    struct ListElement* next;
} ListElement;

void pop(List * list, ListElement * position, int * errorCode) {
    ListElement * temp = position->next;
    position->next = position->next->next;
    free(temp);
}

