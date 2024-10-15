#include <stdio.h>

#define MAX_NUM 10000

void countingSort(int arr[], int n) {
    int count[MAX_NUM * 2 + 1] = {0};

    for (int i = 0; i < n; i++)
        count[arr[i] + MAX_NUM]++;
    int j = 0;
    for (int i = 0; i <= MAX_NUM * 2; i++) {
        while (count[i] > 0) {
            arr[j++] = i - MAX_NUM;
            count[i]--;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    countingSort(arr, n);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

