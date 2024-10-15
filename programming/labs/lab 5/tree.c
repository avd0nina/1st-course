#include "tree.h"

Node *CreateNode(uchar symbol, uint frequency, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->symbol = symbol;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

void FreeHuffmanTree(Node **root) {
    if (root == NULL || *root == NULL) {
        return;
    }
    if ((*root)->left != NULL) {
        FreeHuffmanTree((&(*root)->left));
        FreeHuffmanTree(&((*root)->right));
    }
    free((*root));
    (*root) = NULL;
} 
