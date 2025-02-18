#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsValidInput (int b) {
    if (b < 2 || b > 16) {
        return -1;
    }
    return 0;
}

int Length(char *arr) {
    int length = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        length++;
    }
    return length;
}

long long Expo(int n, int m) {
    long long res = 1;
        if (m >= 0) {
        for (int i = 0; i < m; i++) {
            res *= n;
        }
    }
    return res;
}

int CharToInt(char a) {
    if (a <= '9' && a >= '0')
        return a - '0';
    if (a >= 'a' && a <= 'z')
        return a - 'a' + 10;
    if(a >= 'A' && a <= 'Z')
        return a - 'A' + 10;
    else return -1;
}

char IntToChar(int a) {
    if (a <= 9) {
        return a + '0';
    }
    else return a - 10 + 'a';
}

int IndexOfDot(char *n) {
    for (int i = 0; i < Length(n); i++) {
        if (n[i] == '.')
            return i;
    }
    return Length(n);
}

int CountDots(char *n) {
    int count = 0;
    for (int i = 0; n[i] != '\0'; i++) {
        if (n[i] == '.')
            count++;
    }
    return count;
}

long long ConvertIntegerPart(char *n, int b1) {
    long long res = 0;
    for (int i = 0; i < IndexOfDot(n); i++) {
        int inum = CharToInt(n[i]);
        if (inum >= b1 || inum == -1) {
            return -1;
        }
        res += inum * Expo(b1, IndexOfDot(n) - i - 1);
    }
    return res;
}

double ConvertFractionalPart(char *n, int b1) {
    if (!strchr(n, '.')) {
        return 0;
    }
    double res = 0;
    const int len = Length(n);
    double base_multiplier = 1.0 / b1;
    for (int i = IndexOfDot(n) + 1; i < len; i++) {
        int inum = CharToInt(n[i]);
        if (inum >= b1 || inum == -1) {
            return -1;
        }
        res += inum * base_multiplier;
        base_multiplier /= b1;
    }
    return res;
}

void IntegerToBase(long long n, int b2, char *out) {
    char buffer[256];
    int idx = 0;
    buffer[idx++] = IntToChar(n % b2);
        n /= b2;
    while (n) {
        buffer[idx++] = IntToChar(n % b2);
        n /= b2;
    }
    for (int i = 0; i < idx; i++) {
        out[i] = buffer[idx - i - 1];
    }
    out[idx] = '\0';
}

void FractionalToBase(double fraction, int b2, char *out) {
    out[0] = '.';
    int idx = 1;
    for (int i = 0; i < 12 && fraction > 0; i++) {
        fraction *= b2;
        int intpart = (int)fraction;
        out[idx++] = IntToChar(intpart);
        fraction -= intpart;
    }
    out[idx] = '\0';
}

int main() {
    int b1, b2;
    char x[256];
    if (scanf("%d %d %255s", &b1, &b2, x) != 3) {
        printf("bad input\n");
        return 0;
    }
    if (IsValidInput(b1) == -1 || IsValidInput(b2) == -1) {
        printf("bad input\n");
        return 0;
    }
    if(strchr(x, '.') && Length(x) < 3) {
        printf("bad input\n");
        return 0;
    }
    if (CountDots(x) > 1) {
        printf("bad input\n");
        return 0;
    }

    long long intpart = ConvertIntegerPart(x, b1);
    double fracpart = ConvertFractionalPart(x, b1);

    if (intpart == -1 || fracpart == -1) {
        printf("bad input\n");
        return 0;
    }

    char integerstring[256], fractionalstring[256];

    IntegerToBase(intpart, b2, integerstring);
    FractionalToBase(fracpart, b2, fractionalstring);

    if (strchr(x, '.')) {
        printf("%s%s\n", integerstring, fractionalstring);
    } else {
        printf("%s\n", integerstring);
    }

    return 0;
}
