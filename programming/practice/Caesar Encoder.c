// код цезаря
#include <stdio.h>
#include <stdlib.h>

char EncodeSymbol(char c, int n) {
  if (c >= 'A' && c <= 'Z')
    c = c - 'A' + 'a';
  if (n >= 0)
    n %= 26;
  else
    n = -((-n) % 26);
  c += n;
  if (c < 'a')
    return c + 26;
  if (c > 'z')
    return c - 26;
  return c;
}

char* CaesarEncode(int n, const char* in_name, const char* out_name) {
  FILE* input = fopen(in_name, "r");
  FILE* output = fopen(out_name, "w");
  char c;
  while ((c = fgetc(input)) != EOF) {
    fputc(EncodeSymbol(c, n), output);
  }
  fclose(input);
  fclose(output);
}

int main() {
  CaesarEncode(-3, "input.txt", "output.txt");
  return 0;
}
