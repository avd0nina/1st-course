#include <stdio.h>
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1

typedef enum {
    RED,
    BLACK,
} Colour;

typedef struct Node {
    int data;
    Colour colour;
    struct Node *child[2];
} Node;

typedef struct RBTree {
    Node* tree;
    Node* root;
    int nodes_number;
} RBTree;

int CheckIfNodeIsRed(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->colour == RED;
}

void FlipNodeColors(Node *node) {
    node->colour = node->colour ^ 1;
    node->child[LEFT]->colour = node->child[LEFT]->colour ^ 1;
    node->child[RIGHT]->colour = node->child[RIGHT]->colour ^ 1;
}

Node *RotateSubtree(Node *node, int direction) {
    Node *tmp = node->child[!direction];
    node->child[!direction] = tmp->child[direction];
    tmp->child[direction] = node;
    tmp->colour = node->colour;
    node->colour = RED;
    return tmp;
}

Node *DoubleRotateSubtree(Node *node, int direction) {
    node->child[!direction] = RotateSubtree(node->child[!direction], !direction);
    return RotateSubtree(node, direction);
}

Node *FixRedBlackViolation(Node *node, int direction) {
    if (CheckIfNodeIsRed(node->child[direction])) {
        if (CheckIfNodeIsRed(node->child[!direction])) {
            if (CheckIfNodeIsRed(node->child[direction]->child[direction]) || CheckIfNodeIsRed(node->child[direction]->child[!direction])) {
                FlipNodeColors(node);
            }
        }
        else {
            if (CheckIfNodeIsRed(node->child[direction]->child[direction])) {
                node = RotateSubtree(node, !direction);
            }
            else if (CheckIfNodeIsRed(node->child[direction]->child[!direction])) {
                node = DoubleRotateSubtree(node, !direction);
            }
        }
    }
    return node;
}

Node *InsertNode(Node *tree, Node *root, int index, int data) {
    if (!root) {
        tree[index].data = data;
        tree[index].colour = RED;
        tree[index].child[RIGHT] = NULL;
        tree[index].child[LEFT] = NULL;
        root = &tree[index];
        return root;
    }
    int direction = data > root->data;
    root->child[direction] = InsertNode(tree, root->child[direction], index, data);
    return FixRedBlackViolation(root, direction);
}

int CreateTree(RBTree** rb_tree, int nodes_number) {
    *rb_tree = malloc(sizeof(RBTree));
    if (!*rb_tree) {
        return 0;
    }
    (*rb_tree)->tree = malloc(sizeof(Node) * nodes_number);
    if (!(*rb_tree)->tree) {
        return 0;
    }
    (*rb_tree)->root = NULL;
    (*rb_tree)->nodes_number = nodes_number;
    return 1;
}

void DestroyTree(RBTree** rb_tree) {
    free((*rb_tree)->tree);
    free(*rb_tree);
}

int FillTree(RBTree** rb_tree, const char* input_file_name) {
    FILE *in = fopen(input_file_name, "r");
    if (!in) {
        return 0;
    }
    int nodes_number;
    if (!fscanf(in, "%d", &nodes_number)) {
        fclose(in);
        return 0;
    }
    if (nodes_number <= 0) {
        printf("0");
        fclose(in);
        return 0;
    }
    if (!CreateTree(rb_tree, nodes_number)) {
        fclose(in);
        return 0;
    }
    int tmp;
    for (int i = 0; i < nodes_number; i++) {
        if (!fscanf(in, "%d", &tmp)) {
            DestroyTree(rb_tree);
            fclose(in);
            return 0;
        }
        (*rb_tree)->root = InsertNode((*rb_tree)->tree, (*rb_tree)->root, i, tmp);
    }
    (*rb_tree)->root->colour = BLACK;
    fclose(in);
    return 1;
}

int CalculateBlackHeight(RBTree** rb_tree) {
    int black_nodes_number = 0;
    Node* tmp = (*rb_tree)->root;
    while (tmp) {
        if (tmp->colour == BLACK) {
            black_nodes_number++;
        }
        tmp = tmp->child[LEFT];
    }
    return black_nodes_number;
}

int CalculateTreeHeight(RBTree** rb_tree) {
    return CalculateBlackHeight(rb_tree) + 1;
}

int main(void) {
    const char *input_file_name = "in.txt";
    RBTree* rb_tree = NULL;
    if (!FillTree(&rb_tree, input_file_name))
        return 0;
    printf("%d", CalculateTreeHeight(&rb_tree));
    DestroyTree(&rb_tree);
    return 0;
} 
 
