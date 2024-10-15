#include <stdio.h>
int GCD(int a, int b) {
    while ((a * b) != 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }
    return a + b;
}

int main(void) {
    FILE *input_file = fopen("gcd.in", "r");
    FILE *output_file = fopen("gcd.out", "w");
    int a, b;
    fscanf(input_file, "%d %d", &a, &b);
    fprintf(output_file, "%d", GCD(a,b));
    fclose(input_file);
    fclose(output_file);
    return 0;
}
