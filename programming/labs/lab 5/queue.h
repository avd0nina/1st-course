#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

#define MAX_ALPHABET_LENGTH 256

typedef struct PriorityQueue {
    Node *nodes_array[MAX_ALPHABET_LENGTH];
    int start;
    int end;
} PriorityQueue;

PriorityQueue *CreatePriorityQueue(void);
void InsertNodeIntoQueue(PriorityQueue *queue, Node *node);
Node *GetLeastNode(PriorityQueue *queue);

#endif // QUEUE_H
