#include <stdio.h>
#include <assert.h>

//
// Created by nimrod on 02/07/2022.
//
unsigned char cycle_byte_left(unsigned char b, unsigned int n) {
    unsigned char mask = 0xFF << (8 - n);
    mask |= n;
    mask >>= 8 - n;
    b <<= n;
    return b | n;
}

void cycle_byte_array_left1(unsigned char *pb, int pbsize, unsigned int n) {
    while (n-- != 0) {
        unsigned char next_mask = (pb[pbsize - 1] & 0x80) >> 7;
        for (int i = 0; i < pbsize; ++i) {
            unsigned char mask = (pb[i] & 0x80) >> 7;
            pb[i] <<= 1;
            pb[i] |= next_mask;
            next_mask = mask;
        }
    }
}

void cycle_byte_array_left2(unsigned char* pb, int pbsize, unsigned int n) {
    while(n--) {
        int i;
        unsigned char first_bit = (pb[pbsize-1] & 0x80)? 1 : 0;
        unsigned char bit = 0;
        for(i=0; i<pbsize; i++) {
            unsigned char this_bit = (pb[i] & 0x80)? 1 : 0;
            pb[i] <<= 1;
            pb[i] |= bit;
            bit = this_bit;
        }
        pb[0] |= first_bit;
    }
}


//int main() {
//    printf("%x\n", cycle_byte_left(182, 2));
//    unsigned char c1[4] = "abc";
//    unsigned char c2[4] = "abc";
//    cycle_byte_array_left1(c1, 3, 1);
//    cycle_byte_array_left2(c2, 3, 1);
//    for (int i = 0; i < 3; ++i) {
//        assert(c1[i] == c2[i]);
//    }
//}