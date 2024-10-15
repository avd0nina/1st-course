#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int CloseComment(char a) {
    char s;
    while (scanf("%c", &s) == 1) {
        if (s == '\n') {
            printf("%c", s);
        }
        else if (s == '/' && a == '*') {
            return 1;
        }
        a = s;
    }
    return 0;
}
 
void IsFirstType(void) {
    char s;
    while (scanf("%c", &s) == 1) {
        if (s == '\n') {
            printf("%c", s);
        }
        if (s == '*' && CloseComment(s) == 1) {
            return;
        }
    }
}
 
void IsSecondType(void) {
    char s;
    while (scanf("%c", &s) == 1) {
        if (s == '\n') {
            printf("%c", s);
            return;
        }
    }
}
  
void DetermineType(char c) {
    char s;
    if (scanf("%c", &s) == 1) {
        if (s != '/' && s != '*') {
            printf("%c%c", c, s);
            return;
        }
        else if (s == '/') {
            IsSecondType();
        }
        else {
            IsFirstType();
        }
    }
    else {
        printf("%c", c);
    }
}
 
int main(void){
    freopen("input.txt", "r", stdin);
    char c;
    while (1){
        if (scanf("%c", &c) != 1) {
            break;
        }
        else if (c == '/') {
            DetermineType(c);
        }
        else {
            printf("%c", c);
        }
    }
}
