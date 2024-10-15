#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define TEMPLATE_SIZE 17

typedef unsigned long long int ull;
typedef unsigned char uc;

ull IntPow(const int number, const int power) {
  ull result = 1;
  for (int i = 1; i <= power; i++) {
    result *= number;
  }
  return result;
}

ull CalculateHash(const uc* string) {
  ull hash_sum = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    ull power_result = 1;
    for (int j = 0; j < i; j++) {
      power_result *= 3;
    }
    hash_sum += (string[i] % 3) * power_result;
  }
  return hash_sum;
}

void PrintIndexes(const uc* text,
                  const uc* template,
                  const int index,
                  const int count_iterations) {
  for (int i = 0; template[i] != '\0'; i++) {
    printf("%d ", index + i + 1 + (count_iterations * BUFFER_SIZE));
    if (template[i] != text[index + i]) {
      break;
    }
  }
}

ull UpdateHash(ull partial_hash,
               uc removed_char,
               uc new_char,
               int length_template) {
  partial_hash -= removed_char % 3;
  partial_hash /= 3;
  partial_hash += ((new_char % 3) * IntPow(3, length_template - 1));
  return partial_hash;
}

void SearchTemplate(FILE *file) {
    uc template[TEMPLATE_SIZE];
    uc s;
    int length_template = 0;
    for (; (s = getc(file)) != '\n'; length_template++) {
        template[length_template] = s;
    }
    template[length_template] = '\0';
    ull template_hash = CalculateHash(template);
    printf("%llu ", template_hash);
    uc buffer[TEMPLATE_SIZE + BUFFER_SIZE];
    int i = 0;
    for (; i < length_template; i++) {
        s = getc(file);
        buffer[i] = s;
    }
    buffer[i] = '\0';
    ull partial_hash = CalculateHash(buffer);
    int loop_iterations = 0;
    while (!feof(file)) {
        int length_text = 0;
        length_text = fread(buffer + length_template, 1, BUFFER_SIZE, file);
        for (int i = length_template; i <= length_text + length_template; i++) {
            if (partial_hash == template_hash) {
                PrintIndexes(buffer, template, i - length_template, loop_iterations);
            }
            partial_hash = UpdateHash(partial_hash, buffer[i - length_template],buffer[i], length_template);
        }
        loop_iterations++;
        memcpy(buffer, buffer + BUFFER_SIZE - length_template + 1, length_template);
        memset(buffer + length_template, '\0', BUFFER_SIZE);
    }
}

int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }
  SearchTemplate(file);
  fclose(file);
  return 0;
}
