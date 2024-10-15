#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 1000000
#define LENGTH 8

struct Record {
 int key;
 char word[LENGTH];
};
 
struct RecordList {
 struct Record* records;
 int size;
 int power;
};
 
void Create(struct RecordList* list) {
 list->power = 10;
 list->records = (struct record*)malloc(list->power * sizeof(struct Record));
 list->size = 0;
}
 
void Add(struct RecordList* list, int key, const char* word) {
 if (list->size == list->power) {
  list->power *= 2;
  list->records = (struct Record*)realloc(list->records, list->power * sizeof(struct Record));
 }
 list->records[list->size].key = key;
 strcpy(list->records[list->size].word, word);
 list->size++;
}
 
void Free(struct RecordList* list) {
 free(list->records);
}
 
int main(void) {
 struct RecordList recs[K + 1];
 for (int i = 0; i <= K; i++) {
  Create(&recs[i]);
 }
 int N;
 scanf("%d", &N);
 for (int i = 0; i < N; i++) {
  int key;
  char word[LENGTH];
  scanf("%d %s", &key, word);
  Add(&recs[key], key, word);
 }
 for (int i = 0; i <= K; i++) {
  for (int j = 0; j < recs[i].size; j++) {
   printf("%d %s\n", recs[i].records[j].key, recs[i].records[j].word);
  }
  Free(&recs[i]);
 }
 return 0;
}
// Поиск кратчайшего пути между двумя вершинами
int ShortestPath(Graph graph, int start, int end) {
    Queue *queue = CreateQueue(graph.N);
    bool used[MAX_TOP] = {false};
    int distances[MAX_TOP];
    int parents[MAX_TOP];

    for (int i = 0; i < graph.N; i++) {
        distances[i] = INT_MAX;
        parents[i] = -1;
    }

    distances[start] = 0;
    used[start] = true;
    Enqueue(queue, start);

    while (!IsEmpty(queue)) {
        int current = Dequeue(queue);

        for (int i = 0; i < graph.N; i++) {
            if (graph.matrix[current][i] && !used[i]) {
                used[i] = true;
                distances[i] = distances[current] + 1;
                parents[i] = current;
                Enqueue(queue, i);
            }
        }
    }

    free(queue->elements);
    free(queue);

    if (!used[end]) {
        return -1;
    }

    printf("%d\n", distances[end]);

    int path[MAX_TOP];
    int path_length = 0;
    for (int v = end; v != -1; v = parents[v]) {
        path[path_length++] = v;
    }

    for (int i = path_length - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return distances[end];
}

int main(void) {
    int N;
    scanf("%d", &N);

    Graph graph = CreateGraph(N);

    int start, end;
    scanf("%d %d", &start, &end);

    start--; // Индексация вершин начинается с 0
    end--;

    ShortestPath(graph, start, end);

    return 0;
}
