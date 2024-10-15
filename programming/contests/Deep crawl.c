#include <stdio.h>
#include <stdbool.h>

#define MAX_TOP 100

typedef struct Graph {
    int matrix[MAX_TOP][MAX_TOP];
    int N;
} Graph;

void DFS(Graph graph, int start, bool used[]) {
    used[start] = true;
    for (int i = 0; i < graph.N; ++i) {
        if (graph.matrix[start][i] && !used[i]) {
            DFS(graph, i, used);
        }
    }
}

int CountTops(Graph graph, int start) {
    bool used[MAX_TOP] = {false};
    DFS(graph, start, used);

    int count = 0;
    for (int i = 0; i < graph.N; ++i) {
        if (used[i]) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int N, S;
    scanf("%d %d", &N, &S);

    Graph graph;
    graph.N = N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &graph.matrix[i][j]);
        }
    }

    S--;

    int result = CountTops(graph, S);
    printf("%d\n", result);

    return 0;
}

