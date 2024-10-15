#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct Node {
    uchar symbol;
    uint frequency;
    struct Node *left, *right;
} Node;

Node *CreateNode(uchar symbol, uint frequency, Node *left, Node *right);
void FreeHuffmanTree(Node **root);

#endif // TREE_H
