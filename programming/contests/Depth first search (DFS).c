#include <stdio.h>

void DFS(int matrix[100][100], int N, int used[], int v) {
  for (int i = 0; i < N; i++) {
    if (matrix[v][i] && !used[i]) {
      used[i] = 1;
      DFS(matrix, N, used, i);
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
    int N, S;
    scanf("%d %d", &N, &S);
    int matrix[100][100];
    ScanGraph(matrix, N);
    int count = 0;
    int used[100] = {0};
    DFS(matrix, N, used, S - 1);
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}

