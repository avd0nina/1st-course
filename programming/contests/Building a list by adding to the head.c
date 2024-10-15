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
    int count = 0, x;
    struct List* head = NULL;
    while (scanf("%d", &x) != EOF) {
        List* p = (List*)malloc(sizeof(List));
        p->data = x;
        p->next = head;
        head = p;
    }
    for (List* i = head; i != NULL; i = i->next) {
        if ((i->data < 0) && (i->data % 7 == 0)) {
            count++;
        }
    }
    FreeList(head);
    printf("%d", count);
    return 0;
}

