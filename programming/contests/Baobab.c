#include <stdio.h>
#include <stdbool.h>

void DFS(int matrix[100][100], int N, int used[], int v, int parent, bool* is_tree) {
    used[v] = 1;
    for (int i = 0; i < N; i++) {
        if (matrix[v][i] && !used[i]) {
            DFS(matrix, N, used, i, v, is_tree);
        } else if (matrix[v][i] && used[i] && i != parent) {
            *is_tree = false;
        }
    }
}

void ScanGraph(int matrix[100][100], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

int main(void) {
    int N;
    scanf("%d", &N);
    int matrix[100][100];
    ScanGraph(matrix, N);
    int used[100] = {0};

    bool is_tree = true;
    DFS(matrix, N, used, 0, -1, &is_tree);

    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            is_tree = false;
            break;
        }
    }

    if (is_tree) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}

