#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "huffman.h"

#define FALSE 0
#define TRUE 1

long CalculateByteFrequencies(uint *symbol_frequencies, FILE *file) {
    assert(symbol_frequencies != NULL);
    assert(file != NULL);
    uchar current_symbol;
    long count = 0;
    for (int i = 0; i < MAX_ALPHABET_LENGTH; i++) {
        symbol_frequencies[i] = 0;
    }
    while (fread(&current_symbol, 1, 1, file)) {
        symbol_frequencies[(int)current_symbol]++;
        count++;
    }
    fseek(file, 1, SEEK_SET);
    return count;
}

Node *BuildHuffmanTree(uint *symbol_frequencies) {
    assert(symbol_frequencies != NULL);
    PriorityQueue *queue = CreatePriorityQueue();
    if (queue == NULL) {
        return NULL;
    }
    for (int i = 0; i < MAX_ALPHABET_LENGTH; i++) {
        if (symbol_frequencies[i]) {
            InsertNodeIntoQueue(queue, CreateNode(i, symbol_frequencies[i], 0, 0));
        }
    }
    while (queue->end - queue->start > 0) {
        Node *first_node = GetLeastNode(queue), *second_node = GetLeastNode(queue);
        if (first_node == NULL || second_node == NULL) {
            free(queue);
            return NULL;
        }
        InsertNodeIntoQueue(queue, CreateNode(0, first_node->frequency + second_node->frequency, first_node, second_node));
    }
    Node *root = GetLeastNode(queue);
    free(queue);
    return root;
}

void BuildHuffmanCodes(Node *root, char **codes, char *current_code) {
    assert(root != NULL);
    assert(codes != NULL);
    assert(current_code != NULL);
    const size_t length = strlen(current_code);
    if (root->left == NULL) {
        codes[root->symbol] = (char*)malloc(length + 1);
        if (codes[root->symbol] == NULL) {
            return;
        }
        strcpy(codes[root->symbol], current_code);
    }
    else {
        current_code[length] = '0';
        current_code[length + 1] = '\0';
        if (root->left) {
            BuildHuffmanCodes(root->left, codes, current_code);
        }
        current_code[length] = '1';
        current_code[length + 1] = '\0';
        if (root->right) {
            BuildHuffmanCodes(root->right, codes, current_code);
        }
    }
}

void FreeHuffmanCodes(char **codes) {
    assert(codes != NULL);
    for (int i = 0; i < MAX_ALPHABET_LENGTH; i++) {
        if (codes[i]) {
            free(codes[i]);
        }
    }
}

void InitializeBitBuffer(BitBuffer *bit_buffer, uint buffer_size) {
    assert(bit_buffer != NULL);
    bit_buffer->buffer_size = buffer_size;
    bit_buffer->bit_counter = 8;
    bit_buffer->byte_counter = 0;
    bit_buffer->buffer = (uchar*)malloc(sizeof(uchar) * buffer_size);
    if (bit_buffer->buffer == NULL) {
        return;
    }
    for (uint i = 0; i < buffer_size; i++) {
        bit_buffer->buffer[i] = 0;
    }
}

void WriteByte(FILE *file, BitBuffer *bit_buffer, uchar bit) {
    assert(file != NULL);
    assert(bit_buffer != NULL);
    bit_buffer->buffer[bit_buffer->byte_counter] |= ((bit - '0') << (bit_buffer->bit_counter - 1));
    bit_buffer->bit_counter--;
    if (bit_buffer->bit_counter == 0) {
        fwrite(&bit_buffer->buffer[bit_buffer->byte_counter], sizeof(uchar), 1, file);
        bit_buffer->bit_counter = 8;
        bit_buffer->buffer[bit_buffer->byte_counter] = 0;
    }
}

int ReadBit(BitBuffer *bit_buffer, uchar *bit) {
    assert(bit_buffer != NULL);
    assert(bit != NULL);
    if (bit_buffer->byte_counter >= bit_buffer->buffer_size) {
        return 1;
    }
    *bit = (bit_buffer->buffer[bit_buffer->byte_counter] >> (bit_buffer->bit_counter - 1)) & 1;
    bit_buffer->bit_counter--;
    if (bit_buffer->bit_counter == 0) {
        bit_buffer->byte_counter++;
        bit_buffer->bit_counter = 8;
    }
    return 0;
}

void ReadByte(BitBuffer *bit_buffer, uchar *byte) {
    assert(bit_buffer != NULL);
    assert(byte != NULL);
    *byte = bit_buffer->buffer[bit_buffer->byte_counter] << (8 - bit_buffer->bit_counter);
    bit_buffer->byte_counter++;
    *byte |= bit_buffer->buffer[bit_buffer->byte_counter] >> bit_buffer->bit_counter;
}

void WriteSymbol(FILE *out, BitBuffer *bit_buffer, const char *code) {
    assert(out != NULL);
    assert(bit_buffer != NULL);
    assert(code != NULL);
    for (uint i = 0; i < strlen(code); i++) {
        WriteByte(out, bit_buffer, code[i]);
    }
}

void FlushDataBuffer(FILE *out, BitBuffer *bit_buffer) {
    assert(out != NULL);
    assert(bit_buffer != NULL);
    if (bit_buffer->bit_counter != ONE_BYTE_SIZE) {
        fwrite(&(bit_buffer->buffer[bit_buffer->byte_counter]), 1, 1, out);
    }
}

uchar ReadSymbol(FILE *file, Node *root, BitBuffer *bit_buffer) {
    assert(root != NULL);
    assert(bit_buffer != NULL);
    if (root->left) {
        uchar bit = 0;
        if (ReadBit(bit_buffer, &bit)) {
            if (!fread(bit_buffer->buffer, 1, MAX_BUFFER_LENGTH, file)) {
                return FALSE;
            }
            bit_buffer->byte_counter = 0;
            ReadBit(bit_buffer, &bit);
        }
        if (bit) {
            return ReadSymbol(file, root->right, bit_buffer);
        }
        else {
            return ReadSymbol(file, root->left, bit_buffer);
        }
    }
    else {
        return root->symbol;
    }
}

void PackHuffmanTree(FILE *file, BitBuffer *bit_buffer, Node *root) {
    assert(file != NULL);
    assert(bit_buffer != NULL);
    assert(root != NULL);
    if (root->left == NULL) {
        WriteByte(file, bit_buffer, '0');
        for (int i = 0; i < ONE_BYTE_SIZE; i++) {
            WriteByte(file, bit_buffer, ((root->symbol) >> (ONE_BYTE_SIZE - 1 - i) & 1) + '0');
        }
    }
    else {
        WriteByte(file, bit_buffer, '1');
        PackHuffmanTree(file, bit_buffer, root->left);
        PackHuffmanTree(file, bit_buffer, root->right);
    }
}

void UnpackHuffmanTree(BitBuffer *bit_buffer, Node **root) {
    assert(bit_buffer != NULL);
    assert(root != NULL);
    *root = (Node*)malloc(sizeof(Node));
    if (*root == NULL) {
        return;
    }
    (*root)->frequency = 0;
    uchar bit = 0;
    ReadBit(bit_buffer, &bit);
    if (bit) {
        (*root)->symbol = 0;
        UnpackHuffmanTree(bit_buffer, &((*root)->left));
        UnpackHuffmanTree(bit_buffer, &((*root)->right));
    }
    else {
        (*root)->left = 0;
        (*root)->right = 0;
        uchar symbol;
        ReadByte(bit_buffer, &symbol);
        (*root)->symbol = symbol;
    }
}

int Encode(FILE *in, FILE *out) {
    assert(in != NULL);
    assert(out != NULL);
    uint table_freguency[MAX_ALPHABET_LENGTH];
    const long text_length = CalculateByteFrequencies(table_freguency, in);
    if (!text_length) {
        return FALSE;
    }
    Node *root = BuildHuffmanTree(table_freguency);
    if (root == NULL) {
        return FALSE;
    }
    char* codes[MAX_ALPHABET_LENGTH] = {NULL};
    char current[MAX_ALPHABET_LENGTH] = {0};
    BuildHuffmanCodes(root, codes, current);
    fwrite(&(text_length), 4, 1, out);
    BitBuffer bit_buffer;
    InitializeBitBuffer(&bit_buffer, 1);
    if (bit_buffer.buffer == NULL) {
        FreeHuffmanTree(&root);
        FreeHuffmanCodes(codes);
        return FALSE;
    }
    PackHuffmanTree(out, &bit_buffer, root);
    for (long i = 0; i < text_length; i++) {
        uchar symbol;
        if (fread(&symbol, 1, 1, in) != 1) {
            free(bit_buffer.buffer);
            FreeHuffmanTree(&root);
            FreeHuffmanCodes(codes);
            return FALSE;
        }
        WriteSymbol(out, &bit_buffer, codes[symbol]);
    }
    FlushDataBuffer(out, &bit_buffer);
    free(bit_buffer.buffer);
    FreeHuffmanTree(&root);
    FreeHuffmanCodes(codes);
    return TRUE;
}

int Decode(FILE *in, FILE *out) {
    assert(in != NULL);
    assert(out != NULL);
    Node *root;
    BitBuffer bit_buffer;
    InitializeBitBuffer(&bit_buffer, MAX_BUFFER_LENGTH);
    if (bit_buffer.buffer == NULL) {
        return FALSE;
    }
    uint encoded_char_number = 0;
    if (!fread(&encoded_char_number, 4, 1, in)) {
        free(bit_buffer.buffer);
        return FALSE;
    }
    if (!fread(bit_buffer.buffer, 1, MAX_BUFFER_LENGTH, in)) {
        free(bit_buffer.buffer);
        return FALSE;
    }
    UnpackHuffmanTree(&bit_buffer, &root);
    if (root == NULL) {
        free(bit_buffer.buffer);
        return FALSE;
    }
    for (unsigned long i = 0; i < encoded_char_number; i++) {
        uchar symbol = ReadSymbol(in, root, &bit_buffer);
        fwrite(&symbol, 1, 1, out);
    }
    free(bit_buffer.buffer);
    FreeHuffmanTree(&root);
    return TRUE; 
}
