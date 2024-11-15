#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

NodeValue createValue(int key, char* value) {
    NodeValue nodeValue = { .value = value, .key = key };
    return nodeValue;
}

void printNode(Node* node, bool* errorCode) {
    NodeValue value = getValue(node, errorCode);
    printf("'%d': %s\n", value.key, value.value);
}

int main(void) {
    bool* errorCode = false;
    const char* string = "abccccccdeeee";
    int arrayOfFrequencies[256] = {0};
    for (int i = 0; i < strlen(string); ++i) {
        unsigned char index = string[i];
        ++arrayOfFrequencies[index];
    }
    Node* arrayOfNode[256] = {NULL};
    int notNull = 0;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfFrequencies[i] == 0) {
            continue;
        }
        NodeValue value = createValue(i, arrayOfFrequencies[i]);
        arrayOfNode[i] = createNode(value, &errorCode);
        ++notNull;
    }

    //while (notNull > 1) {
    //    int firstIndexMinElement = -1;
    //    int secondIndexMinElement = -1;

    //}
}
