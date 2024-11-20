#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

typedef struct {
    bool code[256];
    int length;
} CodeEntry;

NodeValue createValue(char value, int frequency) {
    NodeValue nodeValue = { .value = value, .frequency = frequency };
    return nodeValue;
}

void printNode(Node* node, bool* errorCode) {
    NodeValue value = getValue(node, errorCode);
    printf("'%c': %d\n", value.value, value.frequency);
}

void fillOfArrayOfFrequencies(int arrayOfFrequencies[], char* string) {
    for (int i = 0; i < strlen(string); ++i) {
        unsigned char index = string[i];
        ++arrayOfFrequencies[index];
    }
}

int fillOfArrayOfNode(Node* arrayOfNode[], int arrayOfFrequencies[], bool* errorCode) {
    int notNull = 0;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfFrequencies[i] == 0) {
            continue;
        }
        NodeValue value = createValue(i, arrayOfFrequencies[i]);
        arrayOfNode[i] = createNode(value, errorCode);
        ++notNull;
        if (*errorCode) {
            return 0;
        }
    }
    return notNull;
}

int getMinIndex(Node* arrayOfNode[], bool* errorCode) {
    int minIndexElement = -1;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfNode[i] == NULL) {
            continue;
        }
        int frequency = getValue(arrayOfNode[i], errorCode).frequency;
        if (minIndexElement == -1) {
            minIndexElement = i;
            continue;
        }
        if (frequency < getValue(arrayOfNode[minIndexElement], errorCode).frequency) {
            minIndexElement = i;
        }
        if (*errorCode) {
            return -1;
        }
    }
    return minIndexElement;
}

Node* getRootNode(Node* arrayOfNode[], int notNull, bool* errorCode) {
    while (notNull > 1) {
        const int firstIndexMinElement = getMinIndex(arrayOfNode, errorCode);
        Node* firstMinNode = arrayOfNode[firstIndexMinElement];
        arrayOfNode[firstIndexMinElement] = NULL;
        if (*errorCode) {
            return NULL;
        }

        const int secondIndexMinElement = getMinIndex(arrayOfNode, errorCode);
        Node* secondMinNode = arrayOfNode[secondIndexMinElement];
        if (*errorCode) {
            return NULL;
        }

        const int newFrequency = getValue(firstMinNode, errorCode).frequency + getValue(secondMinNode, errorCode).frequency;
        Node* newNode = createNode(createValue('\0', newFrequency), errorCode);
        addLeftChild(newNode, firstMinNode, errorCode);
        addRightChild(newNode, secondMinNode, errorCode);
        arrayOfNode[secondIndexMinElement] = newNode;
        if (*errorCode) {
            return NULL;
        }

        --notNull;
    }

    Node* rootNode = NULL;
    for (int i = 0; i < 256; ++i) {
        if (arrayOfNode[i] == NULL) {
            continue;
        }
        rootNode = arrayOfNode[i];
        break;
    }

    return rootNode;
}

void writeToCodeTable(Node* currentNode, bool* currentCode, int currentCodeLength, CodeEntry codeTable[], bool* errorCode) {
    if (*errorCode) {
        return;
    }
    if (getLeftChild(currentNode, errorCode) == NULL && getRightChild(currentNode, errorCode) == NULL) {
        const unsigned char value = getValue(currentNode, errorCode).value;
        for (int i = 0; i < currentCodeLength; ++i) {
            codeTable[value].code[i] = currentCode[i];
        }
        codeTable[value].length = currentCodeLength;
        return;
    }
    currentCode[currentCodeLength] = false;
    writeToCodeTable(getLeftChild(currentNode, errorCode), currentCode, currentCodeLength + 1, codeTable, errorCode);

    currentCode[currentCodeLength] = true;
    writeToCodeTable(getRightChild(currentNode, errorCode), currentCode, currentCodeLength + 1, codeTable, errorCode);
}

int main(void) {
    const char* string = "abccccccdeeee";
    int arrayOfFrequencies[256] = { 0 };
    bool errorCode = false;
    fillOfArrayOfFrequencies(arrayOfFrequencies, string);
    if (errorCode) {
        return errorCode;
    }

    Node* arrayOfNode[256] = { NULL };
    int notNull = fillOfArrayOfNode(arrayOfNode, arrayOfFrequencies, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    Node* rootNode = getRootNode(arrayOfNode, notNull, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    CodeEntry codeTable[256] = { 0 };
    bool currentCode[256] = { false };
    writeToCodeTable(rootNode, currentCode, 0, codeTable, &errorCode);
    if (errorCode) {
        return errorCode;
    }
    
    bool buffer[8] = {false};
    int bufferIndex = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        CodeEntry entry = codeTable[string[i]];
        for (int j = 0; j < entry.length; ++j) {
            buffer[bufferIndex] = entry.code[j];
            ++bufferIndex;
            if (bufferIndex == 8) {
                unsigned char bufferValue = '\0';
                for (int k = 0; k < 8; ++k) {
                    bufferValue |= buffer[k] << k;
                }
                printf("0x%02X ", bufferValue);
                bufferIndex = 0;
            }
        }
    }
}
