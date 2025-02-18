#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

typedef enum {
    BAD_LENGTH,
    BAD_VERTEX,
    BAD_NUMBER_OF_LINES,
    BAD_NUMBER_OF_VERTICES,
    BAD_NUMBER_OF_EDGES,
    NO_SPANNING_TREE,
    NO_ERRORS
} ErrorType;

typedef struct Subset {
    int parent;
} Subset;

typedef struct Edge {
    int start;
    int end;
    int weight;
} Edge;

typedef struct Graph {
    int vertices_number;
    int edge_number;
    Edge* edges;
} Graph;

Graph* CreateGraph(int N, int M) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices_number = N;
    graph->edge_number = M;
    graph->edges = (Edge*)malloc(M * sizeof(Edge));
    return graph;
}

int ScanAndProcessGraph(FILE* in, Graph* graph, int vertices_number, int edges_number) {
    for (int edge = 0; edge < edges_number; edge++) {
        int start, end;
        ull check_weight;
        if (fscanf(in, "%d %d %llu", &start, &end, &check_weight) < 3) {
            return BAD_NUMBER_OF_LINES;
        }
        if ((start < 1 || start > vertices_number) || (end < 1 || end > vertices_number)) {
            return BAD_VERTEX;
        }
        if (check_weight > INT_MAX) {
            return BAD_LENGTH;
        }
        int weight = (int)check_weight;
        graph->edges[edge].start = start;
        graph->edges[edge].end = end;
        graph->edges[edge].weight = weight;
    }
    return NO_ERRORS;
}

int CompareEdges(const void* e1, const void* e2) {
    const Edge* edge1 = (const Edge*)e1;
    const Edge* edge2 = (const Edge*)e2;
    if (edge1->weight < edge2->weight) {
        return -1;
    }
    if (edge1->weight > edge2->weight) {
        return 1;
    }
    return 0;
}

Subset* CreateDSU(Graph* graph) {
    Subset* subsets = (Subset*)malloc(sizeof(Subset) * (graph->vertices_number + 1));
    for (int v = 1; v <= graph->vertices_number; v++) {
        subsets[v].parent = v;
    }
    return subsets;
}

int FindRoot(Subset* subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = FindRoot(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset* subsets, int x, int y) {
    int x_root = FindRoot(subsets, x);
    int y_root = FindRoot(subsets, y);
    if (rand() % 2 != 0) {
        subsets[x_root].parent = y_root;
    }
    else {
        subsets[y_root].parent = x_root;
    }
}

int FindAndPrintSpanningTree(Graph* graph) {
    int edges_count = 0;
    int result_index = 0;
    int unrelated_vertices_count = graph->vertices_number - 1;
    Edge* result = malloc(sizeof(Edge) * graph->edge_number);
    qsort(graph->edges, graph->edge_number, sizeof(Edge), CompareEdges);
    Subset* subsets = CreateDSU(graph);
    while (edges_count < graph->edge_number) {
        Edge current_edge = graph->edges[edges_count++];
        int x = FindRoot(subsets, current_edge.start);
        int y = FindRoot(subsets, current_edge.end);
        if (x != y) {
            unrelated_vertices_count--;
            result[result_index++] = current_edge;
            Union(subsets, x, y);
        }
    }
    if (unrelated_vertices_count != 0) {
        free(subsets);
        free(result);
        puts("no spanning tree");
        return NO_SPANNING_TREE;
    }
    for (int i = 0; i < result_index; i++) {
        printf("%d %d\n", result[i].start, result[i].end);
    }
    free(subsets);
    free(result);
    return 1;
}
int main(void) {
    int edges_number, vertices_number;
    FILE* in = fopen("in.txt", "r");
    if (!fscanf(in, "%d", &vertices_number)) {
        fclose(in);
        return 0;
    }
    if (!fscanf(in, "%d", &edges_number)) {
        fclose(in);
        return 0;
    }
    if (vertices_number < 0 || vertices_number > 5000) {
        puts("bad number of vertices");
        fclose(in);
        return 0;
    }
    if (edges_number < 0 || edges_number > (vertices_number * (vertices_number + 1) / 2)) {
        puts("bad number of edges");
        fclose(in);
        return 0;
    }
    Graph* graph = CreateGraph(vertices_number, edges_number);
    int error = ScanAndProcessGraph(in, graph, vertices_number, edges_number);
    if (error != NO_ERRORS) {
        switch (error) {
            case BAD_VERTEX:
                puts("bad vertex");
                break;
            case BAD_LENGTH:
                puts("bad length");
                break;
            case BAD_NUMBER_OF_LINES:
                puts("bad number of lines");
                break;
            default:
                puts("Unknown error");
                break;
        }
        free(graph->edges);
        free(graph);
        fclose(in);
        return 0;
    }
    FindAndPrintSpanningTree(graph);
    fclose(in);
    free(graph->edges);
    free(graph);
    return 0;
}
