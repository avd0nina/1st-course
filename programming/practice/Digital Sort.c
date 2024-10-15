#include <stdio.h>
#include <stdlib.h>

int FindMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void CountingSort(int arr[], int n, int position) {
    int count[10] = {0};
    int *b = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        count[(arr[i] / position) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        b[count[(arr[i] / position) % 10] - 1] = arr[i];
        count[(arr[i] / position) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = b[i];
    }
    free(b);
}

void DigitalSort(int arr[], int n) {
    int max = FindMax(arr, n);
    for (int position = 1; max / position > 0; position *= 10) {
        CountingSort(arr, n, position);
    }
}

int main(void) {
    int N;
    scanf("%d", &N);
    if (N < 10000) {
        int *arr = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        DigitalSort(arr, N);
        for (int i = 0; i < N; i++) {
            printf("%d ", arr[i]);
        }
        free(arr);
        return 0;
    }
}
