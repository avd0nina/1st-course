#include <stdlib.h>

#include "queue.h"

PriorityQueue *CreatePriorityQueue(void) {
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    if (queue == NULL) {
        return NULL;
    }
    queue->start = queue->end = -1;
    return queue;
}

void InsertNodeIntoQueue(PriorityQueue *queue, Node *node) {
    if (queue == NULL || node == NULL) {
        return;
    }
    if (queue->start == -1 && queue->end == -1) {
        queue->start++;
        queue->end++;
        queue->nodes_array[queue->start] = node;
        return;
    }
    int i = 0;
    for (i = 0; i <= queue->end; i++) {
        if (node->frequency >= queue->nodes_array[i]->frequency) {
            for (int j = queue->end + 1; j > i; j--) {
                queue->nodes_array[j] = queue->nodes_array[j - 1];
            }
            queue->nodes_array[i] = node;
            queue->end++;
            return;
        }
    }
    queue->end++;
    queue->nodes_array[i] = node;
}

Node *GetLeastNode(PriorityQueue *queue) {
    if (queue == NULL || queue->end < 0) {
        return NULL;
    }
    return queue->nodes_array[queue->end--];
}
