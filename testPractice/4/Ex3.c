#include <stdio.h>

//
// Created by nimrod on 01/07/2022.
//
//unsigned char flip2(unsigned char n) {
//    unsigned char new = 0;
//    for(int i = 0; i < 8 / 2; i ++){
//        new = new | ((n & (1 << i)) << (7 - i*2));
//        new = new | ((n & (1 << (7-i))) >> (7 - i*2));
//    }
//    return new;
//
//}

unsigned char flip1(unsigned char n) {
    unsigned char new = 0;
    for(int i = 0; i < 7; i++) {
        new |= (n & 1);
        new <<= 1;
        n >>= 1;
    }
    new |= (n & 1);
    return new;
}

unsigned int flip_hex(unsigned int n) {
    unsigned int new = 0;
    for(int i = 0; i < 28; i+=4) {
        new |= (n & 15);
        new <<= 4;
        n >>= 4;
    }
    new |= (n & 15);
    return new;
}

//int main() {
//    printf("%0x", flip_hex(4660));
//}