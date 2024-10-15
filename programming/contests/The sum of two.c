#include <stdio.h>

int main(void) {
    FILE *input_file = fopen("sum.in", "r");
    FILE *output_file = fopen("sum.out", "w");
    if (input_file == NULL || output_file == NULL) {
        return 1;
    }
    int A, B;
    fscanf(input_file, "%d %d", &A, &B);
    int sum = A + B;
    fprintf(output_file, "%d", sum);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
