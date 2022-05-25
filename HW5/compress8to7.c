//
// Created by nimrod on 25-May-22.
//
#include <stdio.h>

void runComp(const char input[], const char output[]) {
    FILE *input_file = fopen(input, "r");
    FILE *output_file = fopen(output, "wb");
    uint64_t MAGIC = 0x0087008700870087ll;
    uint64_t size = 0;
    fwrite(&MAGIC, sizeof MAGIC, 1, output_file);
    fwrite(&size, sizeof size, 1, output_file);
    unsigned int c;
    int shift = 1;
    unsigned int prevChar = fgetc(input_file);
    if (prevChar == -1) {
        return;
    }
    while ((c = fgetc(input_file)) != EOF) {
        if (c & (1 << 7)) {
            fprintf(stderr, "%s/%u: Char at %lu is not an ASCII char!\n\n",
                    __FILE__, __LINE__, size);
        }
        unsigned char temp = c << (8 - shift);
        unsigned char new = prevChar | temp;
        shift++;
        size++;
        if (shift == 9) {
            shift = 1;
        } else {
            fputc(new, output_file);
        }
        prevChar = c >> (shift - 1);
        fflush(output_file);
    }
    fseek(output_file, 64 / 8, SEEK_SET);
    fwrite(&size, sizeof size, 1, output_file);
    fclose(output_file);
    fclose(input_file);
}

//int main(int argc, char *argv[]) {
//    char *input = argv[1];
//    char *output = argv[2];
//    runComp(input, output);
//}
