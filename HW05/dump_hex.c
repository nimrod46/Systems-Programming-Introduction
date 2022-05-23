#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//
// Created by nimrod on 23-May-22.
//
void print_hex(const char *block) {
    long c = strtol(block, 0, 16);
    if (c == strtol("0", 0, 16)) {
        //printf("\n");
        return;
    }
    if (c == strtol("0a", 0, 16)) {
        printf("\n");
        return;
    }
    printf("%c", c);
}


bool nextBlock(const char src[], char dst[], unsigned int offset, unsigned int *dst_size) {
    unsigned int i = offset;
    unsigned int maxLen = strlen(src);
    unsigned int dest_l = strlen(dst);
    if (maxLen <= i) {
        return false;
    }
    for (int j = 0; j < dest_l; ++j) {
        dst[j] = '\0';
    }
    while (maxLen > i && src[i] != ' ') {
        dst[i - offset] = src[i];
        i++;
    }
    dst[i - offset] = src[i];

    unsigned int t = (i - offset) + 1;
    *dst_size = t;
    return true;
}

int main(int argc, char *argv[]) {

    FILE *input = fopen(argv[1], "rb");
    char *buff = NULL;
    size_t buf_size = 0;
    while (getline(&buff, &buf_size, input) != EOF) {
        char offsetBlock[8];
        unsigned int i = 0;
        unsigned int dst_size = 0;
        nextBlock(buff, offsetBlock, i, &dst_size);
        i += dst_size;
        char nextHex[4];
        //printf("%s\n", buff);
        while (nextBlock(buff, nextHex, i, &dst_size)) {
            i += dst_size;
            print_hex(nextHex);
            nextHex[3] = '\0';
            nextHex[2] = '\0';
            print_hex(nextHex);
        }
        //printf("\n");
    }
}
