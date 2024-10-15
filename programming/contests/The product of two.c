#include <stdio.h>

int main(void) {
    FILE *input_file = fopen("product.in", "r");
    FILE *output_file = fopen("product.out", "w");
    long long int A, B;
    fscanf(input_file, "%lld %lld", &A, &B);
    
    long long int product = A * B;
    fprintf(output_file, "%lld", product);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
