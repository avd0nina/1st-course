#include <stdio.h>
#include <stdbool.h>
#define MAX_NUMBER 100

void BFS(int matrix[MAX_NUMBER][MAX_NUMBER], int N, int start, int end) {
    bool used[MAX_NUMBER] = {false};
    int distance[MAX_NUMBER] = {0}, path[MAX_NUMBER];
    for (int i = 0; i < MAX_NUMBER; i++) {
        path[i] = -1;
    }
    int queue[MAX_NUMBER], front = 0, rear = 0;
    queue[rear++] = start;
    used[start] = true;
    while (front != rear) {
        int tmp = queue[front++];
        for (int i = 0; i < N; i++) {
            if (matrix[tmp][i] && !used[i]) {
                queue[rear++] = i;
                used[i] = true;
                distance[i] = distance[tmp] + 1;
                path[i] = tmp;
            }
        }
    }
    if (used[end] && distance[end] == 0){
        printf("%d\n", distance[end]);
    }
    else if (used[end] && distance[end] != 0) {
        printf("%d\n", distance[end]);
        int i = end;
        int j = 0;
        int result[MAX_NUMBER];
        while(i != -1) {
            result[j++] = i;
            i = path[i];
        }
        for(i = j - 1; i >= 0; i--)
            printf("%d ", result[i] + 1);
    }
    else if (!used[end]) {
        printf("-1");
    }
}

int main(void) {
    int N;
    int matrix[MAX_NUMBER][MAX_NUMBER];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int start, end;
    scanf("%d %d", &start, &end);
    BFS(matrix, N, start - 1, end - 1);
    return 0;
}
