// Nimrod Machlav - 315230185
// Dany Reznik - 205953821
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


void print_hex(const char padding[], int chr) {
    char format[5] = {};
    strcat(format, "%");
    strcat(format, padding);
    strcat(format, "x");
    printf(format, chr);
}

void dump_hex(FILE *input) {
    int byte_count = 0;
    print_hex("07", byte_count);
    bool is_second_byte = true;
    int prev;
    int c;
    while ((c = fgetc(input)) != EOF) {
        if (is_second_byte) {
            is_second_byte = false;
            printf(" ");
            prev = c;
            continue;
        }
        is_second_byte = true;
        print_hex("02", c);
        print_hex("02", prev);
        byte_count += 2;
        if (byte_count % 16 == 0) { //Current last row is full
            printf("\n");
            print_hex("07", byte_count);
        }
    }
    if (!is_second_byte) { //Odd number of bytes
        byte_count++;
        print_hex("02", '\0');
        print_hex("02", prev);
    }
    if (byte_count % 16 != 0) { //Last row isn't full
        printf("\n");
        print_hex("07", byte_count);
    }
}

void run_dump_hex_on_file(const char file_name[]) {
    FILE *input = fopen(file_name, "rb");
    if (!input) {
        fprintf(stderr, "%s/%u: File %s not found! \n\n",
                __FILE__, __LINE__, file_name);
        exit(-1);
    }

    dump_hex(input);

    fclose(input);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Illegal arguments! Usage: dump_hex <input_file_name>");
        exit(-1);
    }
    run_dump_hex_on_file(argv[1]);
}


