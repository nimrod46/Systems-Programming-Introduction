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

//int main(int argc, char *argv[]) {
//
//    FILE *input = fopen(argv[1], "rb");
//    int currentBit = 0;
//    printf("%07x", currentBit);
//    bool firstBit = true;
//    int prev;
//    int c;
//    while ((c = fgetc(input)) != EOF) {
//        if (firstBit) {
//            firstBit = !firstBit;
//            printf(" ");
//            prev = c;
//            continue;
//        }
//        firstBit = !firstBit;
//        print_hex(c);
//        print_hex(prev);
//        currentBit += 2;
//        if (currentBit % 16 == 0) {
//            printf("\n");
//            printf("%07x", currentBit);
//        }
//    }
//    fclose(input);
//    if(!firstBit) {
//        currentBit++;
//        print_hex('\0');
//        print_hex(prev);
//    }
//    printf("\n");
//    printf("%07x", currentBit);
//}
