#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000001
  
typedef struct Tokens_s {
    int num;
    char **arr;
} Tokens;
  
void TokensSplit(Tokens *tokens, const char *str, const char *delims) {
    int current_i = 0, i_str = -1, is_start = 1;
    tokens->num = 0;
    for (const char *i = str; *i != 0; ++i) {
        int is_delim = 0;
        for (const char *d = delims; *d != 0; ++d) {
            if (*i == *d) {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) {
            is_start = 1;
        } 
        else {
            tokens->num += is_start;
            is_start = 0;
        }
    }
    tokens->arr = (char **)malloc(tokens->num * sizeof(char *));
    current_i = 0;
    for (const char *i = str; *i != 0; ++i) {
        int is_delim = 0;
        for (const char *d = delims; *d != 0; ++d) {
            if (*i == *d) {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) {
            if (i_str != -1) {
                current_i += 1;
            }
        i_str = -1;
        } 
        else {
            i_str++;
            if (i_str == 0) {
                int temp = 0;
                const char *temp_i = i;
                while (*temp_i != 0) {
                    int is_temp_delim = 0;
                    for (const char *d = delims; *d != 0; ++d) {
                        if (*temp_i == *d) {
                            is_temp_delim = 1;
                            break;
                        }
                    }
                    if (is_temp_delim) {
                        break;
                    }
                    temp++, temp_i++;
                }
                tokens->arr[current_i] = (char *)calloc(temp + 1, sizeof(char));
            }
            tokens->arr[current_i][i_str] = *i;
        }
    }
}
  
void TokensFree(Tokens *tokens) {
    for (int i = 0; i < tokens->num; ++i) {
        free(tokens->arr[i]);
    }
    free(tokens->arr);
    free(tokens);
}
  
int main(void) {
    char words[N];
    scanf("%s", words);
    char del[5] = ".,;:";
    Tokens *token = (Tokens *)calloc(1, sizeof(Tokens));
    TokensSplit(token, words, del);
    printf("%d", token->num);
    for (int i = 0; i < token->num; ++i) {
        printf("\n%s", token->arr[i]);
    }
    TokensFree(token);
    return 0;
}
