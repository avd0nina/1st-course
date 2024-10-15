#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main(void) {
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 char current;
 int count = 0;
 for (int i = 0; i < 10001; ++i) {
     scanf("%c\n", &current);
     if (current != '.') {
         for (i + 1; i < 10001; ++i) {
             scanf("%c\n", &current);
             if (current == '.') {
                 break;
             }
             else {
                 continue;
             }
         }
         count += 1;
     }
     else {
         continue;
     }
 }
 printf("%d", count);
 return 0;
}
