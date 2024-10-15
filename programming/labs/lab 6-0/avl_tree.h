#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct Node {
    int value;
    unsigned char height;
    struct Node *left;
    struct Node *right;
} Node;

unsigned char GetHeight(Node *tree);
int CalculateBalanceFactor(Node *tree);
void FixHeight(Node *tree);
Node *RotateLeft(Node *root);
Node *RotateRight(Node *root);
Node *BalanceTree(Node *tree);
Node *Insert(Node *tree, int value, Node *avl_nodes);

#endif // AVL_TREE_H 
