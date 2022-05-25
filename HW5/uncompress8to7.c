//
// Created by nimrod on 25-May-22.
//
#include <stdio.h>

void runUncomp(const char input[], const char output[]) {
    FILE *input_file = fopen(input, "r");
    FILE *output_file = fopen(output, "wb");
    uint64_t MAGIC;
    uint64_t size;
    fread(&MAGIC, sizeof(MAGIC), 1 , input_file);
    fread(&size, sizeof(size), 1 , input_file);
    unsigned int c;
    int shift = 7;
    unsigned char mask = 0;
    while ((c = fgetc(input_file)) != EOF) {
        unsigned char temp = (c << (8 - shift));
        temp = temp >> 1;
        unsigned char new = temp | mask;
        mask = (0xff << (shift)) & c;
        mask = mask >> shift;
        shift--;
        fputc(new, output_file);
        fflush(output_file);
        if(shift == 0) {
            shift = 7;
            fputc(mask, output_file);
            mask= 0;
        }
    }
}

//int main(int argc, char *argv[]) {
//    char *input = argv[1];
//    char *output = argv[2];
//    runUncomp(input, output);
//    return 0;
//}
