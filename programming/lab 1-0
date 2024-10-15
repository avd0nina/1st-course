#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT_CHARS 256
#define SIZE_PATTERN 16
#define SIZE_BUFFER 4096

typedef unsigned char uc;

int FindMax(int a, int b) {
  return (a > b) ? a : b;
}

int BuildOffsetTable(uc* pattern, int size, uc* chars_shift) {
  int counter = 0;
  for (int i = 0; i < SHIFT_CHARS; i++) {
    chars_shift[i] = size;
  }
  for (int i = 0; i < size - 1; i++) {
    if (pattern[i] == pattern[size - 1]) {
      counter += 1;
    }
    chars_shift[(int)pattern[i]] = size - i - 1;
  }
  if (counter == 0) {
    chars_shift[(int)pattern[size - 1]] = size;
  }
  return 0;
}

int FindSubstring(uc* buf, uc* pattern, uc* chars_shift, long* global_shift) {
  FILE* output = fopen("out.txt", "a+");
  int buf_len = (int)strlen((char*)buf);
  int pattern_len = (int)strlen((char*)pattern);
  long shift = 0;
  while (shift + pattern_len <= buf_len) {
    int counter = pattern_len - 1;
    while (counter >= 0 && pattern[counter] == buf[shift + counter]) {
      fprintf(output, "%ld ", *global_shift + shift + counter + 1);
      counter--;
    }
    if (counter < 0) {
      shift += (shift + pattern_len < buf_len) ? pattern_len : 1;
    } else {
      fprintf(output, "%ld ", *global_shift + shift + counter + 1);
      shift += FindMax(1, chars_shift[(int)buf[shift + pattern_len - 1]]);
    }
  }
  *global_shift += shift;
  fclose(output);
  return 0;
}

int main() {
  uc pattern[SIZE_PATTERN + 2], buf[SIZE_BUFFER + 2], chars_shift[SHIFT_CHARS];
  int buffer_len = 0;
  uc letter_of_pattern;
  FILE* input = fopen("in.txt", "r");
  for (int i = 0; i <= SIZE_PATTERN; i++) {
    if (fread(&letter_of_pattern, sizeof(char), 1, input)) {
      if (letter_of_pattern == '\n') {
        pattern[i] = '\0';
        break;
      }
      pattern[i] = letter_of_pattern;
    }
  }
  BuildOffsetTable(pattern, (int)strlen((char*)pattern), chars_shift);
  buffer_len = fread(buf, sizeof(char), SIZE_BUFFER, input);
  if (buffer_len == 0) {
    fclose(input);
    return 0;
  }
  long global_shift = 0;
  while (!feof(input)) {
    buf[buffer_len] = '\0';
    FindSubstring(buf, pattern, chars_shift, &global_shift);
    memset(buf, 0, sizeof(buf));
    buffer_len = fread(buf, sizeof(char), SIZE_BUFFER, input);
  }
  buf[buffer_len] = '\0';
  FindSubstring(buf, pattern, chars_shift, &global_shift);
  fclose(input);
  return 0;
}
