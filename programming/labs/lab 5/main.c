#include <stdio.h>
#include "huffman.h"

int main(void) {
    uchar symbol;
    FILE *in = fopen("in.txt", "rb");
    FILE *out = fopen("out.txt", "wb");
    if (in == NULL || out == NULL) {
        if (in) {
            fclose(in);
        }
        if (out) {
            fclose(out);
        }
        return 1;
    }
    if (fread(&symbol, 1, 1, in) != 1) {
        fclose(in);
        fclose(out);
        return 1;
    }
    if (symbol == 'c') {
        Encode(in, out);
    }
    else {
        Decode(in, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}
