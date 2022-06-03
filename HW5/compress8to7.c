// Nimrod Machlav - 315230185
// Dany Reznik - 205953821
//
#include <stdio.h>
#include <stdlib.h>

#define MAGIC 0x0087008700870087ll

uint64_t write_8to7(FILE *input_file, FILE *output_file) {
    uint64_t size = 0;
    unsigned int c;
    int shift = 1;
    unsigned int prev_char = fgetc(input_file);
    if (prev_char == -1) {
        return 0;
    }
    while ((c = fgetc(input_file)) != EOF) {
        if (c & (1 << 7)) {
            fprintf(stderr, "%s/%u: Char at %lu is not an ASCII char!\n\n",
                    __FILE__, __LINE__, size);
        }
        unsigned char temp = c << (8 - shift);
        unsigned char new_char = prev_char | temp; //New char after compress data from current char is writen at the end
        shift++;
        size++;
        if (shift == 9) {
            shift = 1;
        } else {
            fputc(new_char, output_file); //Avoid writing the same char twice when new_char byte starts
        }
        prev_char = c >> (shift - 1); //save current char by current shift state
    }
    if (shift != 8) { //If file isn't 
        size++;
        fputc(prev_char, output_file);
    }

    return size;
}

void run_comp_on_file(const char input_file_name[], const char output_file_name[]) {
    FILE *input_file = fopen(input_file_name, "r");
    if(!input_file) {
        fprintf(stderr, "%s/%u: File %s not found! \n\n",
                __FILE__, __LINE__, input_file_name);
        exit(-1);
    }
    FILE *output_file = fopen(output_file_name, "wb");
    if(!output_file) {
        fprintf(stderr, "%s/%u: Failed creating a file: %s \n\n",
                __FILE__, __LINE__, output_file_name);
        exit(-1);
    }
    uint64_t size = 0;
    uint64_t magic = MAGIC;
    fwrite(&magic, sizeof magic, 1, output_file);
    fwrite(&size, sizeof size, 1, output_file);

    size = write_8to7(input_file, output_file);

    fclose(input_file);
    fseek(output_file, 64 / 8, SEEK_SET); //move cursor to after MAGIC value
    fwrite(&size, sizeof size, 1, output_file);
    fclose(output_file);
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Illegal arguments! Usage: compress8to7 <input_file_name> <output_file_name>");
        exit(-1);
    }
    char *input = argv[1];
    char *output = argv[2];
    run_comp_on_file(input, output);
}
