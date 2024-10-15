#include <stdio.h>

int main(void) {
    FILE *input_file = fopen("apbtest.in", "r");
    FILE *output_file = fopen("apbtest.out", "w");
    long long int c;
    fscanf(input_file, "%lld", &c);
    long long int a = c / 2;
    long long int b = c - a;
    fprintf(output_file, "%lld %lld", a, b);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
