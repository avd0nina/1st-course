#include <stdio.h>
#include <stdlib.h>
  
typedef struct List {
    int data;
    struct List* next;
} List;
  
List* CreateNewList(int data) {
    List* sorted = (List*)malloc(sizeof(List));
    sorted->data = data;
    sorted->next = NULL;
    return sorted;
}
  
void InsertNode(List** head, int data) {
    List * sorted = CreateNewList(data);
    if (*head == NULL) {
        *head = sorted;
    }
    else if (data < (*head)->data) {
        sorted->next = *head;
        *head = sorted;
    }
    else {
        List* now = *head;
        while (now->next != NULL && data > now->next->data) {
            now = now->next;
        }
        if (now->next != NULL && data == now->next->data) {
            free(sorted);
            return;
        }
        sorted->next = now->next;
        now->next = sorted;
    }
}
  
void FreeList(List* head) {
    List* p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}
  
void PrintList(List* head) {
    List* now = head;
    while (now != NULL) {
        if (now->next != NULL && now->data != now->next->data)
            printf("%d ", now->data);
        if (now->next == NULL)
            printf("%d ", now->data);
            now = now->next;
    }
    printf("\n");
}
  
int main(void) {
    List* head = NULL;
    int data;
    while (scanf("%d", &data) == 1) {
        InsertNode(&head, data);
    }
    PrintList(head);
    FreeList(head);
    return 0;
}
