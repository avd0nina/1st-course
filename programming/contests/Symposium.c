#include <stdio.h>
#include <stdlib.h>

int Сompare(const void* A, const void* B) {
  const int* num1 = (const int*)A;
  const int* num2 = (const int*)B;
  return *num1 - *num2;
}

int main(void) {
  FILE* output_file = freopen("symposium.out", "w", stdout);
  FILE* input_file = freopen("symposium.in", "r", stdin);
  int n;
  scanf("%d", &n);
  int* arr = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }
  int longest = 1, current = 1;
    qsort(arr, n, sizeof(int), Сompare);
  for (int i = 1; i < n; ++i) {
    if ((long long)arr[i] >= 2 * (long long)arr[i - 1]) {
      if (longest < current)
        longest = current;
      current = 1;
    } else {
      ++current;
    }
  }
  if (longest < current)
    longest = current;
  printf("\n%d", longest);
  fclose(output_file);
  fclose(input_file);
  free(arr);
  return 0;
}
