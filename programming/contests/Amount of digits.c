#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) {
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 char a, b;
 long long n1 = 0;
 long long n2 = 0;
 while (scanf("%c", &a) == 1) {
    if (a >= '0' && a <= '9') {
        n2 += a - '0';
        scanf("%c", &b);
        while (b >= '0' && b <= '9') {
            if (b >= '0' && b <= '9') {
                n2 = n2 * 10 + b - '0';
            }
            scanf("%c", &b);
        }
    }
    n1 += n2;
    n2 = 0;
  }
  printf("%lld", n1);
  return 0;
}
