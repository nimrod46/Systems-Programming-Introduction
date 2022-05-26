//
// Created by nimrod on 25-May-22.
//
#include <stdio.h>

#define MAGIC 0x0087008700870087ll

uint64_t decompress_file(FILE *input_file, FILE *output_file) {
    uint64_t byte_count = 0;
    int c;
    int shift = 7;
    unsigned char last_compressed_bits = 0;
    while ((c = fgetc(input_file)) != EOF) {
        unsigned char temp = (c << (8 - shift));
        temp = temp >> 1;
        unsigned char new = temp | last_compressed_bits; //cpy last compressed bits into current char

        last_compressed_bits = (0xff << (shift)) & c; //cpy current char compressed bits
        last_compressed_bits = last_compressed_bits >> shift;

        shift--;
        fputc(new, output_file);
        byte_count++;

        if(shift == 0) {
            shift = 7;
            if(last_compressed_bits == 0) { //Avoid writing garbage data
                continue;
            }
            fputc(last_compressed_bits, output_file); //New byte? so "last_compressed_bits" should contain the nex char, lets print it!
            last_compressed_bits= 0; //And reset it....
            byte_count++; //And ofc count it
        }
    }
    return byte_count;
}

void runDecomp(const char input[], const char output[]) {
    FILE *input_file = fopen(input, "r");
    FILE *output_file = fopen(output, "wb");
    uint64_t magic;
    uint64_t original_file_size;
    fread(&magic, sizeof(magic), 1 , input_file);
    if(magic != MAGIC) {
        fprintf(stderr, "%s/%u: Header does not match! Make sure you are trying to decompress a valid 8to7 compress file\n\n",
                __FILE__, __LINE__);
        return;
    }
    fread(&original_file_size, sizeof(original_file_size), 1 , input_file);

    uint64_t byte_count = decompress_file(input_file, output_file);

    if(original_file_size != byte_count) {
        fprintf(stderr, "%s/%u: File size does not match!\n\n",
                __FILE__, __LINE__);
    }
}



//int main(int argc, char *argv[]) {
//    char *input = argv[1];
//    char *output = argv[2];
//    runDecomp(input, output);
//    return 0;
//}
