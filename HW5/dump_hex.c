#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//
// Created by nimrod on 23-May-22.
//

void print_hex(int c) {
    printf("%02x", c);
}

void run_dump_hex(const char file_name[]) {
    FILE *input = fopen(file_name, "rb");
    int byte_count = 0;
    printf("%07x", byte_count);
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
        print_hex(c);
        print_hex(prev);
        byte_count += 2;
        if (byte_count % 16 == 0) {
            printf("\n");
            printf("%07x", byte_count);
        }
    }
    fclose(input);
    if(!is_second_byte) {
        byte_count++;
        print_hex('\0');
        print_hex(prev);
    }
    if(byte_count % 16 != 0) {
        printf("\n");
        printf("%07x", byte_count);
    }
}

//int main(int argc, char *argv[]) {
//    run_dump_hex(argv[1]);
//}


