#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include "tree.h"
#include "queue.h"

#define MAX_ALPHABET_LENGTH 256
#define ONE_BYTE_SIZE 8
#define MAX_BUFFER_LENGTH 1000000

typedef struct BitBuffer {
    uchar *buffer;
    uint buffer_size;
    uint byte_counter;
    uint bit_counter;
} BitBuffer;

int Encode(FILE *in, FILE *out);
int Decode(FILE *in, FILE *out);

#endif // HUFFMAN_H
