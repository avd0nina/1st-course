#include <stdio.h>

int CountOnes(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int main(void) {
    int N;
    scanf("%d", &N);
    unsigned int arr[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }
    unsigned int max_num = 0;
    int max_ones = 0;
    for (int i = 0; i < N; ++i) {
        int ones = CountOnes(arr[i]);
        if (ones > max_ones) {
            max_ones = ones;
            max_num = arr[i];
        }
    }

    printf(max_num);
    return 0;
}

