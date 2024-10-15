#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int data;
    struct List* next;
} List;

void FreeList(List* head) {
    List* p = head;
    while (p != NULL) {
        List* next = p->next;
        free(p);
        p = next;
    }
}

int main(void) {
    int count = 0, sum = 0, x;
    List* head = NULL;
    List* end = NULL;
    while (scanf("%d", &x) != EOF) {
        List* p = (List*)malloc(sizeof(List));
        p->data = x;
        p->next = NULL;
        if (head == NULL) {
            head = p;
            end = p;
        } else {
            end->next = p;
            end = p;
        }
        sum += x;
        count++;
    }
    int avg = (count == 0) ? 0 : sum / count;
    FreeList(head);
    printf("%d", avg);
    return 0;
}

