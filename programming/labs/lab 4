#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 10024

typedef struct {
  int stack[MAX_STACK_SIZE];
  int top;
} Stack;

void Push(Stack* s, int num) {
  if (s->top == MAX_STACK_SIZE - 1) {
    printf("Error: stack overflow\n");
    return;
  }
  s->stack[++s->top] = num;
}

int Pop(Stack* s) {
  if (s->top == -1) {
    printf("Error: stack underflow\n");
    return 0;
  }
  return s->stack[s->top--];
}

int Eval(char* exp) {
  Stack s = {.top = -1};
  char* token = strtok(exp, " ");
  while (token != NULL) {
    if (strlen(token) == 1 && !isdigit(token[0])) {
      int b = Pop(&s);
      int a = Pop(&s);
      switch (token[0]) {
        case '+':
          Push(&s, a + b);
          break;
        case '-':
          Push(&s, a - b);
          break;
        case '*':
          Push(&s, a * b);
          break;
        case '/':
          if (b == 0) {
            printf("%s", "division by zero");
            exit(0);
          }
          Push(&s, a / b);
          break;
        default:
          printf("Error: invalid operator\n");
          return 0;
      }
    } else {
      Push(&s, atof(token));
    }
    token = strtok(NULL, " ");
  }
  return Pop(&s);
}

int Precedence(char c) {
  switch (c) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '(':
    case ')':
    case '\0':
      return 0;
    default:
      printf("Error: invalid operator\n");
      return -1;
  }
}

void InfixToPostfix(const char* infix, char* postfix) {
  Stack s = {.top = -1};
  int p = 0;
  for (int i = 0; infix[i] != '\0'; i++) {
    if (isdigit(infix[i])) {
      postfix[p++] = infix[i];
      if (!isdigit(infix[i + 1])) {
        postfix[p++] = ' ';
      }
    } else if (infix[i] == '(') {
      Push(&s, infix[i]);
    } else if (infix[i] == ')') {
      while (s.top > -1 && s.stack[s.top] != '(') {
        postfix[p++] = ' ';
        postfix[p++] = Pop(&s);
        postfix[p++] = ' ';
      }
      if (s.top > -1 && s.stack[s.top] == '(') {
        Pop(&s);
      } else {
        printf("Error: mismatched parentheses\n");
        return;
      }
    } else {
      while (s.top > -1 && Precedence(infix[i]) <= Precedence(s.stack[s.top])) {
        postfix[p++] = ' ';
        postfix[p++] = Pop(&s);
        postfix[p++] = ' ';
      }
      Push(&s, infix[i]);
      postfix[p++] = ' ';
    }
  }
  while (s.top > -1) {
    postfix[p++] = ' ';
    postfix[p++] = Pop(&s);
    postfix[p++] = ' ';
  }
  postfix[p] = '\0';
}

int SyntaxCheck(const char* expr) {
  int paren_count = 0;
  int op_count = 0;
  int op_expected = 0;
  int num_count = 0;
  for (int i = 0; expr[i] != '\0'; i++) {
    if (isdigit(expr[i])) {
      num_count++;
      while (isdigit(expr[++i])) {
      }
      i--;
      op_expected = 1;
    } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
               expr[i] == '/') {
      if (!op_expected) {
        return 0;
      }
      op_count++;
    } else if (expr[i] == '(') {
      paren_count++;
    } else if (expr[i] == ')') {
      paren_count--;
      if ((paren_count < 0) || (i > 0 && expr[i - 1] == '(')) {
        return 0;
      }
    } else if (expr[i] != ' ' && expr[i] != '\n') {
      return 0;
    }
  }
  if (paren_count != 0 || op_count >= num_count || !op_expected ||
      (op_count == 0 && num_count > 1)) {
    return 0;
  }
  return 1;
}

int main() {
  char infix[MAX_STACK_SIZE];
  if (fgets(infix, MAX_STACK_SIZE, stdin)) {
    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
      infix[--len] = '\0';
    }
  }
  int valid = SyntaxCheck(infix);
  if (valid) {
    char postfix[MAX_STACK_SIZE];
    InfixToPostfix(infix, postfix);
    printf("%d\n", Eval(postfix));
  } else {
    printf("%s", "syntax error");
  }
  return 0;
}
