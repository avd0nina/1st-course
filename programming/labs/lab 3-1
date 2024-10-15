#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void QuickSort(int *arr, int start, int end) {
  if (end <= start) {
    return;
  }
  int i = start;
  int j = end;
  int mid_el = arr[(end + start) / 2];
  while (i <= j) {
    while (arr[i] < mid_el) {
      i++;
    }
    while (arr[j] > mid_el) {
      j--;
    }
    if (i <= j) {
      Swap(&arr[i], &arr[j]);
      i++;
      j--;
    }
  }
  QuickSort(arr, start, j);
  QuickSort(arr, i, end);
}

int main() {
  int N;
  if (scanf("%d", &N) != 1) {
    printf("bad input\n");
    return 0;
  }
  int *arr = (int *)malloc(N * sizeof(int));
  if (N >= 0 && N <= 2000000) {
    for (int i = 0; i < N; i++) {
      int check;
      if (scanf("%d", &check) != 1) {
        printf("bad input\n");
        return 0;
      } else {
        arr[i] = check;
      }
    }
    QuickSort(arr, 0, N - 1);
    for (int i = 0; i < N; i++) {
      printf("%d ", arr[i]);
    }
  }
  free(arr);
  return 0;
}
