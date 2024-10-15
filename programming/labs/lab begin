#include <stdio.h>
#include <stdbool.h> 
#include <limits.h> 

bool int_range(long long val) {
    return val <= INT_MAX && val >= INT_MIN;
}

bool int_overflow(int a, int b) {
    if ((a > INT_MAX - b) && b > 0) {
        return true; 
    }
    if ((a < INT_MIN - b) && b < 0) {
        return true; 
    }
    return false;
}

int main() {
    FILE *file = fopen("in.txt", "r");

    
    int N, i;
    long long sum = 0;
    long long numbers[10];

    if(fscanf(file, "%d", &N) != 1 || N < 1 || N > 10) {
        printf("bad input");
        fclose(file);
        return 0;
    }

    for(i = 0; i < N; i++) {
        if(fscanf(file, "%lld", &numbers[i]) != 1) {
            printf("bad input");
            fclose(file); 
            return 0;
        }

        if (!int_range(numbers[i])) {
            printf("bad input");
            fclose(file);
            return 0;
        }
    }

    int ch = fgetc(file);
    if (ch != '\n' && ch != EOF) {
        printf("bad input");
        fclose(file); 
        return 0;
    }

    for(i = 0; i < N; i++) {
        if(int_overflow(sum, numbers[i])) {
            printf("overflow");
            fclose(file);
            return 0;
        }
        sum += numbers[i];
    }

    fclose(file);
    printf("%d\n", (int)sum);
    return 0;
}
