#include <stdio.h>
#include <string.h>

char *DivideTokens(char *str, const char *delim) {
    static char *next_token = NULL;
    char *token_start;
    if (str != NULL) {
        next_token = str;
    }
    while (*next_token && strchr(delim, *next_token)) {
        next_token++;
    }
    if (!*next_token) {
        return NULL;
    }
    token_start = next_token;
    while (*next_token && !strchr(delim, *next_token)) {
        next_token++;
    }
    if (*token_start != '\0') {
        *next_token = '\0';
        next_token++;
        return token_start;
    }
    if (!*next_token) {
        return NULL;
    }
    return DivideTokens(NULL, delim);
}

//int main(void) {
//    char str[100];
//    scanf("%s", str);
//    char delim[1];
//    scanf("%s", delim);
//    char *token = DivideTokens(str, delim);
//    while (token != NULL) {
//        printf("%s\n", token);
//        token = DivideTokens(NULL, delim);
//    }
//    return 0;
//}

