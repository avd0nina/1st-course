#include <stdio.h>

int GCD(int a, int b) {
    if (b == 0) {
        return a;
    }
    return GCD(b, a % b);
}

int main(void) {
    FILE *input_file = fopen("numbers.in", "r");
    FILE *output_file = fopen("numbers.out", "w");
    int A, B;
    fscanf(input_file, "%d", &A, &B);
    int gcd = GCD(A, B);
    long long int X, Y;
    fclose(input_file);
    fclose(output_file);
    return 0;
}
