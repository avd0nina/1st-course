#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define BLOCK_SIZE 8

double* IdToHeap[301000];

typedef struct MyDoubleHeap {
    double* arr;
    struct MyDoubleHeap* head;
} MyDoubleHeap;

MyDoubleHeap my_arr;
MyDoubleHeap* ptr = &my_arr;

MyDoubleHeap InitializeAllocator(int slots_count) {
    ptr->arr = (double*)malloc(slots_count * BLOCK_SIZE);
    ptr->head = ptr;
    for (int i = 0; i < slots_count; i++)
        ptr->arr[i] = i + 1 == slots_count ? (int64_t)NULL : (int64_t)((ptr->arr) + i + 1);
}

double* AllocDouble(MyDoubleHeap* heap) {
    return heap->head->arr;
}

void FreeDouble(MyDoubleHeap* heap, double* ptr) {
    double* now = heap->head->arr;
    heap->head->arr = ptr;
    *(ptr) = (int64_t)(now);
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int blocks_number, operations_number, operation_type, slot_number;
    double value, *now;
    fscanf(stdin, "%d %d", &blocks_number, &operations_number);
    InitializeAllocator(blocks_number);
    for (int i = 0; i < operations_number; i++) {
        fscanf(stdin, "%d", &operation_type);
        switch (operation_type) {
            case 0:
                fscanf(stdin, "%lf", &value);
                fprintf(stdout, "%p\n", AllocDouble(ptr));
                if (ptr->head->arr != NULL) {
                    now = ptr->head->arr;
                    ptr->head->arr = (int64_t)(*now);
                    IdToHeap[i] = now;
                    *now = value;
                }
                break;
            case 1:
                fscanf(stdin, "%d", &slot_number);
                FreeDouble(ptr, IdToHeap[slot_number]);
                break;
            case 2:
                fscanf(stdin, "%d", &slot_number);
                fprintf(stdout, "%0.5lf\n", *(IdToHeap[slot_number]));
                break;
        }
    }
    free(ptr->arr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
