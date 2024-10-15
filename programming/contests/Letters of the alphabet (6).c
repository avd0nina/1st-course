#include <stdio.h>
#include<stdlib.h>
 
int main(void) {
    char arr[26];
    int n, i, j, left, right;
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf_s(" %c", &arr[i]);
    }
    i = n - 2;
    j = n - 1;
    char place;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i -= 1;
    }
    while (arr[j] <= arr[i]) {
        j-=1;
    }
    place = arr[i];
    arr[i] = arr[j];
    arr[j] = place;
    right = n - 1;
    left = i + 1;
    while (left < right) {
        place = arr[left];
        arr[left] = arr[right];
        arr[right] = place;
        right-=1;
        left+=1;
    }
    for (int i = 0; i < n; i++) {
        printf("%c ", arr[i]);
    }
    return 0;
}
