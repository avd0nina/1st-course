#include <stdio.h>

//int Fibonacci(int n) {
//    if (n <= 1) {
//        return 1;
//    }
//    else {
//        return Fibonacci(n - 1) + Fibonacci(n - 2);
//    }
//}
//
//int main(void) {
//    FILE *input_file = fopen("fib.in", "r");
//    FILE *output_file = fopen("fib.out", "w");
//    int n;
//    fscanf(input_file, "%d", &n);
//    int fibonacci = Fibonacci(n);
//    fprintf(output_file, "%d", fibonacci);
//    fclose(input_file);
//    fclose(output_file);
//    return 0;
//}

int main(void) {
    FILE *input_file = fopen("fib.in", "r");
    FILE *output_file = fopen("fib.out", "w");
    int n;
    fscanf(input_file, "%d", &n);
    int fib = 1, prev = 1, temp;
    for (int i = 2; i <= n; ++i) {
        temp = fib;
        fib += prev;
        prev = temp;
    }
    fprintf(output_file, "%d", fib);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
