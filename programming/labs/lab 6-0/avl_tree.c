#include "avl_tree.h"

#include <stddef.h>

unsigned char GetHeight(Node *tree) {
    return tree ? tree->height : 0;
}

int CalculateBalanceFactor(Node *tree) {
    return GetHeight(tree->right) - GetHeight(tree->left);
}

void FixHeight(Node *tree) {
    unsigned char hl = GetHeight(tree->left);
    unsigned char hr = GetHeight(tree->right);
    tree->height = (hl > hr ? hl : hr) + 1;
}

Node *RotateLeft(Node *root) {
    Node *right = root->right;
    root->right = right->left;
    right->left = root;
    FixHeight(root);
    FixHeight(right);
    return right;
}

Node *RotateRight(Node *root) {
    Node *left = root->left;
    root->left = left->right;
    left->right = root;
    FixHeight(root);
    FixHeight(left);
    return left;
}

Node *BalanceTree(Node *tree) {
    FixHeight(tree);
    if (CalculateBalanceFactor(tree) == 2) {
        if (CalculateBalanceFactor(tree->right) < 0) {
            tree->right = RotateRight(tree->right);
        }
        return RotateLeft(tree);
    } 
    else if (CalculateBalanceFactor(tree) == -2) {
        if (CalculateBalanceFactor(tree->left) > 0) {
            tree->left = RotateLeft(tree->left);
        }
        return RotateRight(tree);
    }
    return tree;
}

Node *Insert(Node *tree, int value, Node *avl_nodes) {
    if (!tree) {
        avl_nodes->value = value;
        avl_nodes->left = avl_nodes->right = NULL;
        avl_nodes->height = 1;
        return avl_nodes;
    }
    if (value < tree->value) {
        tree->left = Insert(tree->left, value, avl_nodes);
    } 
    else {
        tree->right = Insert(tree->right, value, avl_nodes);
    }
    return BalanceTree(tree);
}
 
