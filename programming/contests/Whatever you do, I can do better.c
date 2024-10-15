#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
 
int main(void) {
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 char n1, n2, n3;
 for (int i = 0; i < 30 ; ++i) {
  scanf("%c", &n2);
  if (n2 == '.') {
   break;
  }
  n3 = n1;
  n1 = n2;
  if (i == 0) {
   continue;
  }
  else {
   printf("%c", n3);
  }
 }
 if (n1 == 'r' && n3 == 'e') {
  printf("st");
 }
 else if (n1 == 'e') {
  printf("er");
 }
 else {
  printf("%cer", n1);
 }
}
