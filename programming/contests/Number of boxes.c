#include <stdio.h>
#include <stdlib.h>
 
int main(void) {
    int N, a, b, c, c_max;
    long long otvet = 0;
    scanf_s("%d", &N);
    for (a = 1; a * a * a <= N; ++a) {
        for (b = a; a * b * b <= N; ++b) {
            c_max = N / (a * b);
            if (c_max >= b) {
                otvet += c_max - b + 1;
            }
        }
    }
    printf("%lld", otvet);
    return 0;
}
