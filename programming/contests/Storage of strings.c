#include <stdio.h>
#include <stdlib.h>

#define LIMIT 1000000
 
int main(void) {
    char* arr[LIMIT];
    int N, t, l, i = 0, count = 0;
    char *str, letter;
    scanf("%d", &N);
    while (scanf("%d %d", &t, &l) != -1) {
        if (t == 0) {
            str = (char*)malloc(l + 10);
            arr[i] = str;
            scanf("%s", str);
            i++;
        }
        if (t == 1) {
            free(arr[l]);
            arr[l] = NULL;
        }
        if (t == 2) {
            printf("%s\n", arr[l]);
        }
        if (t == 3) {
            scanf(" %c", &letter);
            for (int j = 0; arr[l][j] != 0; j++) {
                if (arr[l][j] == letter){
                    count += 1;
                }
            }
            printf("%d\n", count);
            count = 0;
        }
    }
    for (int j = 0; j < LIMIT; j++) {
        if (arr[j] != NULL){
            free(arr[j]);
        }
     }
    return 0;
}
