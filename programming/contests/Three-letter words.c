#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) {
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 char n1, n2, n3, n4;
 int c = 0;
 scanf("%c%c%c%c", &n1, &n2, &n3, &n4);
 if (n2 == 'A' && n4 == '.')
  printf("FITS");
 else
  printf("DOES NOT FIT");
}
