#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quick_sort.h"

#define LENGTH 10
#define BUFFER_SIZE 16

void BadInput(void) {
    printf("bad input\n");
    exit(EXIT_SUCCESS);
}

void Reverse(char *str, int start, int end) {
    for (int i = start, j = end; i < j; i++, j--) {
        Swap(&str[i], &str[j]);
    }
}

int FindTurnPoint(const char *str, int length) {
    for (int i = length - 2; i >= 0; i--) {
        if (str[i] < str[i + 1]) {
            return i;
        }
    }
    return -1;
}

int ElementForSwap(const char *str, int turn_point, int length) {
    for (int i = length - 1; i > turn_point; i--) {
        if (str[i] > str[turn_point]) {
            return i;
        }
    }
    return -1;
}

void NextPermutation(char *str, int suff_turn, int element_swap) {
    Swap(&str[suff_turn], &str[element_swap]);
    Reverse(str, suff_turn + 1, strlen(str) - 1);
}

int IsValid(const char *str) {
    int used[LENGTH] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        if (++used[str[i] - '0'] > 1) {
            return 0;
        }
    }
    return 1;
}

void PrintPermutations(char* permut, int length, int permut_count) {
    for (int i = 0; i < permut_count; i++) {
        int suff_turn = FindTurnPoint(permut, length);
        if (suff_turn != -1) {
            int swap = ElementForSwap(permut, suff_turn, length);
            NextPermutation(permut, suff_turn, swap);
            printf("%s\n", permut);
        } else {
            return;
        }
    }
}

int main(void) {
    char permut[BUFFER_SIZE] = {0};
    if (scanf("%15[^\n]\n", permut) != 1) {
        return EXIT_FAILURE;
    }
    size_t length = strlen(permut);

    int permut_count = 0;
    if (length > LENGTH || !IsValid(permut) ||
        scanf("%d", &permut_count) != 1) {
        BadInput();
    }

    PrintPermutations(permut, length, permut_count);

    return EXIT_SUCCESS;
}
