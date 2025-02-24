#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  NO_ERROR = 0,
  ERROR,
  BAD_NUMBER_OF_LINES,
  BAD_NUMBER_OF_VERTICES,
  BAD_NUMBER_OF_EDGES,
  BAD_VERTEX,
  BAD_LENGTH,
  IMPOSSIBLE_TO_SORT,
} ErrorType;

typedef struct ShortestPath {
  unsigned int* min_path;
  char* used;
  short int* parent;
} ShortestPath;

typedef struct Graph {
  int vertices_number;
  int edge_number;
  int start;
  int end;
  unsigned int* weights;
} Graph;

int InitializeShortestPath(ShortestPath** shortest_path, int vertices_number) {
  *shortest_path = malloc(sizeof(ShortestPath));
  if (!*shortest_path) {
    return ERROR;
  }
  (*shortest_path)->min_path = malloc(sizeof(unsigned int) * vertices_number);
  if (!(*shortest_path)->min_path) {
    return ERROR;
  }
  (*shortest_path)->used = malloc(sizeof(char) * vertices_number);
  if (!(*shortest_path)->used) {
    return ERROR;
  }
  (*shortest_path)->parent = malloc(sizeof(short int) * vertices_number);
  if (!(*shortest_path)->parent) {
    return ERROR;
  }
  return NO_ERROR;
}

void DestroyShortestPath(ShortestPath** shortest_path) {
  free((*shortest_path)->min_path);
  free((*shortest_path)->used);
  free((*shortest_path)->parent);
  free(*shortest_path);
}

ErrorType CreateGraph(Graph** graph, int vertices_number) {
  *graph = malloc(sizeof(Graph));
  if (!*graph) {
    return ERROR;
  }
  (*graph)->vertices_number = vertices_number;
  int size = vertices_number * vertices_number;
  (*graph)->weights = malloc(sizeof(unsigned int) * size);
  if (!(*graph)->weights) {
    return ERROR;
  }
  return NO_ERROR;
}

ErrorType CheckInput(FILE* in,
                     int* vertices_number,
                     int* start,
                     int* end,
                     int* edge_number) {
  if (fscanf(in, "%d", vertices_number) != 1) {
    return BAD_NUMBER_OF_LINES;
  }
  if (*vertices_number < 0 || *vertices_number > 5000) {
    return BAD_NUMBER_OF_VERTICES;
  }
  if (fscanf(in, "%d %d", start, end) != 2) {
    return BAD_NUMBER_OF_LINES;
  }
  if (*start < 1 || *end < 1 || *start > *vertices_number ||
      *end > *vertices_number) {
    return BAD_VERTEX;
  }
  if (fscanf(in, "%d", edge_number) != 1) {
    return BAD_NUMBER_OF_LINES;
  }
  if (*edge_number < 0 ||
      *edge_number > (*vertices_number + 1) * (*vertices_number) / 2) {
    return BAD_NUMBER_OF_EDGES;
  }
  return NO_ERROR;
}

ErrorType ScanAndProcessGraph(Graph** graph, const char* input_file_name) {
  int vertices_number, start, end, edge_number;
  FILE* in = fopen(input_file_name, "r");
  if (!in) {
    return ERROR;
  }
  ErrorType input_check =
      CheckInput(in, &vertices_number, &start, &end, &edge_number);
  if (input_check != NO_ERROR) {
    fclose(in);
    return input_check;
  }
  if (CreateGraph(graph, vertices_number) != NO_ERROR) {
    fclose(in);
    return ERROR;
  }
  (*graph)->edge_number = edge_number;
  (*graph)->end = end;
  (*graph)->start = start;
  for (int i = 0; i < (*graph)->vertices_number * (*graph)->vertices_number;
       ++i) {
    (*graph)->weights[i] = 0;
  }
  for (int i = 0; i < edge_number; ++i) {
    int a, b, weight;
    if (fscanf(in, "%d %d %d", &a, &b, &weight) != 3) {
      fclose(in);
      return BAD_NUMBER_OF_LINES;
    }
    if (a < 1 || b < 1 || a > vertices_number || b > vertices_number) {
      fclose(in);
      return BAD_VERTEX;
    }
    if (weight <= 0 || weight > INT_MAX) {
      fclose(in);
      return BAD_LENGTH;
    }
    (*graph)->weights[(*graph)->vertices_number * (a - 1) + (b - 1)] = weight;
    (*graph)->weights[(*graph)->vertices_number * (b - 1) + (a - 1)] = weight;
  }
  fclose(in);
  return NO_ERROR;
}

void DestroyGraph(Graph** graph) {
  if (*graph) {
    free((*graph)->weights);
  }
  free(*graph);
}

ErrorType PrintPath(Graph** graph, ShortestPath* shortest_path, const char* output_file_name) {
  FILE* out = fopen(output_file_name, "w");
  if (!out) {
    return ERROR;
  }
  for (int i = 0; i < (*graph)->vertices_number; ++i) {
    if (shortest_path->used[i]) {
      if (shortest_path->min_path[i] > INT_MAX) {
        fprintf(out, "INT_MAX+ ");
      } else {
        fprintf(out, "%u ", shortest_path->min_path[i]);
      }
    } else {
      fprintf(out, "oo ");
    }
  }
  fprintf(out, "\n");
  if (!shortest_path->used[(*graph)->end - 1]) {
    fprintf(out, "no path\n");
    fclose(out);
    return NO_ERROR;
  }
  int count_int_max = 0;
  for (int i = 0; i < (*graph)->vertices_number; ++i) {
    if (shortest_path->min_path[i] == UINT_MAX) {
      continue;
    }
    if (shortest_path->min_path[i] <= INT_MAX) {
      continue;
    }
    count_int_max++;
    for (int j = i; j < (*graph)->vertices_number; ++j) {
      if ((*graph)->weights[(*graph)->vertices_number * i + j]) {
        count_int_max++;
      }
    }
  }
  if (count_int_max >= 2 &&
      shortest_path->min_path[(*graph)->end - 1] > INT_MAX) {
    fprintf(out, "overflow\n");
    fclose(out);
    return NO_ERROR;
  }
  for (int from = (*graph)->end - 1; from != (*graph)->start - 1;
       from = shortest_path->parent[from]) {
    fprintf(out, "%d ", from + 1);
  }
  fprintf(out, "%d \n", (*graph)->start);
  fclose(out);
  return NO_ERROR;
}

ErrorType CalculateShortestPath(Graph** graph, const char* output_file_name) {
  int vertices_number = (*graph)->vertices_number;
  ShortestPath* shortest_path = NULL;
  InitializeShortestPath(&shortest_path, vertices_number);
  for (int i = 0; i < vertices_number; ++i) {
    shortest_path->used[i] = 0;
    shortest_path->min_path[i] = UINT_MAX;
  }
  shortest_path->min_path[(*graph)->start - 1] = 0;
  for (int i = 0; i < vertices_number; ++i) {
    int v = -1;
    for (int j = 0; j < vertices_number; ++j) {
      if (!shortest_path->used[j] &&
          (v == -1 ||
           shortest_path->min_path[j] < shortest_path->min_path[v])) {
        v = j;
      }
    }
    if (shortest_path->min_path[v] == UINT_MAX) {
      PrintPath(graph, shortest_path, output_file_name);
      DestroyShortestPath(&shortest_path);
      return NO_ERROR;
    }
    shortest_path->used[v] = 1;
    for (int to = 0; to < vertices_number; ++to) {
      int weight = (*graph)->weights[vertices_number * v + to];
      if (!weight) {
        continue;
      }
      if (weight + shortest_path->min_path[v] >=
                shortest_path->min_path[to] ||
            shortest_path->used[to]) {
        continue;
      }
      if (weight + shortest_path->min_path[v] <= INT_MAX) {
        shortest_path->min_path[to] = weight + shortest_path->min_path[v];
      } else {
        shortest_path->min_path[to] = UINT_MAX - 1;
      }
      shortest_path->parent[to] = v;
    }
  }
  PrintPath(graph, shortest_path, output_file_name);
  DestroyShortestPath(&shortest_path);
  return NO_ERROR;
}

void PrintError(ErrorType error) {
  switch (error) {
    case ERROR:
      printf("error");
      break;
    case BAD_NUMBER_OF_LINES:
      printf("bad number of lines");
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
    case IMPOSSIBLE_TO_SORT:
      printf("impossible to sort");
      break;
    case BAD_LENGTH:
      printf("bad length");
      break;
    default:
      printf("unknown error");
      break;
  }
}

int main(void) {
  Graph* graph = NULL;
  const char *input_file_name = "in.txt", *output_file_name = "out.txt";
  ErrorType error = ScanAndProcessGraph(&graph, input_file_name);
  if (error != NO_ERROR) {
    PrintError(error);
    DestroyGraph(&graph);
    return 0;
  }
  CalculateShortestPath(&graph, output_file_name);
  DestroyGraph(&graph);
  return 0;
}
