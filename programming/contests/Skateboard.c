#include <stdio.h>

int main(void) {
    FILE *input_file = fopen("skateboard.in", "r");
    FILE *output_file = fopen("skateboard.out", "w");
    int n, i, count = 0;
    fscanf(input_file, "%d", &n);
    int coords[n];
    for (i = 0; i < n; ++i) {
        fscanf(input_file, "%d", &coords[i]);
    }
    for (i = 1; i < n - 1; ++i) {
        if (coords[i] > coords[i - 1] && coords[i] > coords[i + 1]) {
            count++;
        }
    }
    fprintf(output_file, "%d", count);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
