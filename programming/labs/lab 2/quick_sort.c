#include "quick_sort.h"

void Swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void QuickSort(char *arr, int start, int end) {
    if (start >= end) {
        return;
    }
    int pivotIndex = start;
    char pivotValue = arr[end];
    for (int i = start; i < end; i++) {
        if (arr[i] < pivotValue) {
            Swap(&arr[i], &arr[pivotIndex]);
            pivotIndex++;
        }
    }
    Swap(&arr[pivotIndex], &arr[end]);

    QuickSort(arr, start, pivotIndex - 1);
    QuickSort(arr, pivotIndex + 1, end);
}
