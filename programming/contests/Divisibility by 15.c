#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main(void) {
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 char current, last;
 int number, sum = 0, s;
 for (int i = 0; i < 500; ++i) {
    scanf("%c", &current);
    number = current - '0';
    sum += number;
    if (current == '.') {
         break;
    }
    s = sum;
    last = current;
 }
 if (last == '0' && s % 3 == 0 || last == '5' && s % 3 == 0) {
    printf("YES");
 }
 else {
    printf("NO");
    }
}
