#include <stdio.h>
#include <stdlib.h>

void Swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void Heapify(int arr[], int n, int i) {
  int root = i;
  int left_child = 2 * i + 1;
  int right_child = 2 * i + 2;
  if (left_child < n && arr[left_child] > arr[root]) {
    root = left_child;
  }
  if (right_child < n && arr[right_child] > arr[root]) {
    root = right_child;
  }
  if (root != i) {
    Swap(&arr[i], &arr[root]);
    Heapify(arr, n, root);
  }
}

void HeapSort(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    Heapify(arr, n, i);
  }
  for (int i = n - 1; i >= 0; i--) {
    Swap(&arr[0], &arr[i]);
    Heapify(arr, i, 0);
  }
}

int main() {
  int N;
  if (scanf("%d", &N) != 1) {
    printf("bad input\n");
    return 0;
  }
  int* arr = (int*)malloc(N * sizeof(int));
  if (N >= 0 && N <= 2000000) {
    for (int i = 0; i < N; i++) {
      int check;
      if (scanf("%d", &check) != 1) {
        printf("bad input\n");
        return 0;
      } else
        arr[i] = check;
    }
    HeapSort(arr, N);
    for (int i = 0; i < N; i++) {
      printf("%d ", arr[i]);
    }
  }
  free(arr);
  return 0;
}
