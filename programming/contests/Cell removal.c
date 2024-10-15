#include <stdio.h>

void DFS(char matrix[100][100], int M, int N, int used[100][100], int x, int y) {
    if (x < 0 || x >= M || y < 0 || y >= N || used[x][y] || matrix[x][y] == '.') {
        return;
    }
    used[x][y] = 1;
    DFS(matrix, M, N, used, x - 1, y);
    DFS(matrix, M, N, used, x + 1, y);
    DFS(matrix, M, N, used, x, y - 1);
    DFS(matrix, M, N, used, x, y + 1);
}

int main(void) {
    int M, N;
    scanf("%d %d", &M, &N);
    char matrix[100][100];
    for (int i = 0; i < M; i++) {
        scanf("%s", matrix[i]);
    }
    int used[100][100] = {0};
    int count = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!used[i][j] && matrix[i][j] == '#') {
                count++;
                DFS(matrix, M, N, used, i, j);
            }
        }
    }
    printf("%d\n", count);
    return 0;
}
