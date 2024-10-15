#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

int main(void) {
    FILE *in = fopen("in.txt", "r");
    if (!in) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    int N;
    if (fscanf(in, "%d", &N) != 1) {
        fclose(in);
        return EXIT_FAILURE;
    }
    Node *avl_nodes = (Node *)malloc(N * sizeof(Node));
    if (!avl_nodes) {
        fclose(in);
        return EXIT_FAILURE;
    }
    Node *tree = NULL;
    for (int i = 0; i < N; i++) {
        int num;
        if (fscanf(in, "%d", &num) != 1) {
            free(avl_nodes);
            fclose(in);
            return EXIT_FAILURE;
        }
        tree = Insert(tree, num, &avl_nodes[i]);
    }
    printf("%d\n", GetHeight(tree));
    free(avl_nodes);
    fclose(in);
    return EXIT_SUCCESS;
} 
