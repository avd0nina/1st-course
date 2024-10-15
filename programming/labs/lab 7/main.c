#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h" 

const unsigned int kBitsInUInt = sizeof(unsigned int) * 8;

typedef enum {
    NO_ERROR,
    BAD_NUMBER_OF_VERTICES,
    BAD_NUMBER_OF_EDGES,
    BAD_VERTEX,
    BAD_NUMBER_OF_LINES,
    IMPOSSIBLE_TO_SORT
} ErrorType;

typedef enum {
    WHITE,
    GREY,
    BLACK
} VertexColor;

typedef struct Graph {
    int vertices_number;
    int edge_number;
    unsigned int *matrix;
} Graph;

ErrorType CheckInput(int vertices_number, int edge_number) {
    if (vertices_number < 0 || vertices_number > 2000) {
        return BAD_NUMBER_OF_VERTICES;
    }
    else if (edge_number < 0 || edge_number > (vertices_number * (vertices_number + 1) / 2)) {
        return BAD_NUMBER_OF_EDGES;
    }
    return NO_ERROR;
}

Graph *CreateGraph(int vertices_number, int edge_number) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices_number = vertices_number, graph->edge_number = edge_number;
    unsigned int matrix_size = ((vertices_number + 1) * (vertices_number + 1)) / kBitsInUInt + 1;
    graph->matrix = malloc(matrix_size * sizeof(unsigned int));
    for (unsigned int i = 0; i < matrix_size; i++) {
        graph->matrix[i] = 0;
    }
    return graph;
}

void DestroyGraph(Graph *graph) {
    free(graph->matrix);
    free(graph);
}

ErrorType CheckNumberOfVertices(unsigned short start, unsigned short end, int vertices_number) {
    if (start < 1 || start > vertices_number || end < 1 || end > vertices_number) {
        return BAD_VERTEX;
    }
    return NO_ERROR;
}

ErrorType ScanAndProcessGraph(FILE *in, Graph *graph) {
    for (int i = 0; i < graph->edge_number; i++) {
        unsigned short start, end;
        if (fscanf(in, "%hu %hu", &start, &end) < 2) {
            return BAD_NUMBER_OF_LINES;
        }
        if (CheckNumberOfVertices(start, end, graph->vertices_number) != NO_ERROR) {
            return BAD_VERTEX;
        }
        int num = start * graph->vertices_number + end;
        graph->matrix[num / kBitsInUInt] |= 1 << (kBitsInUInt - (num % kBitsInUInt));
    }
    return NO_ERROR;
}

ErrorType DFS(Graph *graph, unsigned short start_vertex, VertexColor *vertices_color, Stack *result) {
    vertices_color[start_vertex] = GREY;
    for (int i = 1; i <= graph->vertices_number; i++) {
        int index = (start_vertex * graph->vertices_number) + i;
        if (graph->matrix[index / kBitsInUInt] & (1 << (kBitsInUInt - index % kBitsInUInt))) {
            if (vertices_color[i] == GREY) {
                return IMPOSSIBLE_TO_SORT;
            }
            else if (vertices_color[i] != BLACK) {
                if (DFS(graph, i, vertices_color, result) != NO_ERROR) {
                    return IMPOSSIBLE_TO_SORT;
                }
            }
        }
    }
    vertices_color[start_vertex] = BLACK;
    PushIntoStack(result, start_vertex);
    return NO_ERROR;
}

ErrorType PerformTopologicalSort(Graph *graph, Stack *result) {
    VertexColor vertices_color[graph->vertices_number + 1];
    for (int i = 1; i <= graph->vertices_number; i++) {
        vertices_color[i] = WHITE;
    }
    for (int v = 1; v <= graph->vertices_number; v++) {
        if (vertices_color[v] != BLACK) {
            if (DFS(graph, v, vertices_color, result) != NO_ERROR) {
                return IMPOSSIBLE_TO_SORT;
            }
        }
    }
    return NO_ERROR;
}

void PrintError(ErrorType error) {
    switch (error) {
        case NO_ERROR:
            printf("no error");
            break;
        case BAD_NUMBER_OF_VERTICES:
            printf("bad number of vertices");
            break;
        case BAD_NUMBER_OF_EDGES:
            printf("bad number of edges");
            break;
        case BAD_VERTEX:
            printf("bad vertex");
            break;
        case BAD_NUMBER_OF_LINES:
            printf("bad number of lines");
            break;
        case IMPOSSIBLE_TO_SORT:
            printf("impossible to sort");
            break;
        default:
            printf("unknown error");
            break;
    }
}

int main(void) {
    int vertices_number, edges_number;
    FILE *in = fopen("in.txt", "r");
    if (fscanf(in, "%d", &vertices_number) < 1 || fscanf(in, "%d", &edges_number) < 1) {
        printf("Bad number of lines");
        fclose(in);
        return 0;
    }
    ErrorType input_error = CheckInput(vertices_number, edges_number);
    if (input_error != NO_ERROR) {
        PrintError(input_error);
        fclose(in);
        return 0;
    }
    Graph *graph = CreateGraph(vertices_number, edges_number);
    ErrorType graph_error = ScanAndProcessGraph(in, graph);
    if (graph_error != NO_ERROR) {
        PrintError(graph_error);
        DestroyGraph(graph);
        fclose(in);
        return 0;
    }
    Stack *result = CreateStack(graph->vertices_number);
    ErrorType sort_error = PerformTopologicalSort(graph, result);
    if (sort_error != NO_ERROR) {
        PrintError(sort_error);
        DestroyGraph(graph);
        DestroyStack(result);
        fclose(in);
        return 0;
    }
    PrintStack(result);
    DestroyGraph(graph);
    DestroyStack(result);
    fclose(in);
    return 0;
}
