#include <stdio.h>
#include <stdbool.h>

#include "list.h"

int main(void) {
    bool errorCode = false;
    List* list = createList(&errorCode);
    return errorCode;
}