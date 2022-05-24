//
// Created by nimrod on 24-May-22.
//

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>


bool check_bit(unsigned int n, unsigned int index) {
    unsigned int b = 1 << index;
    return n & b;
}

int even_bits(unsigned int n) {
    unsigned int mask = 0x5555;
    n = n & mask;
    unsigned int c = 0;
    while (n != 0) {
        c += n % 2;
        n = n >> 1;

    }
    return c;
}

unsigned int flip_even_bits(unsigned int n) {
    for (int i = 0; i < sizeof(unsigned int) * 8; i += 2) {
        n = n ^ (1 << i);
    }
    return n;
}

unsigned int turn_on_high_bits(unsigned int n, unsigned int index) {
    unsigned int mask = ~((1 << index) - 1);
    //unsigned int mask = 0xFFFFFFFF << index;
    return n | mask;
}

//1101
//0001
//   0
//  0
unsigned int reverse_bits(unsigned int n) {
    unsigned int new = 0;
    int size = sizeof (unsigned int) * 8;
    for (int i = 0; i < size; ++i) {
        unsigned int l = n & (1 << (i));
        new = new << 1;
        new = new | (l>>i);
    }
    return new;
}


//int main() {
//    assert(check_bit(0x9, 3));
//    assert(even_bits(9) == 1);
//    assert(even_bits(8) == 0);
//    printf("%d\n", flip_even_bits(8));
//    printf("%d\n", turn_on_high_bits(8, 5));
//    printf("%d\n", reverse_bits(1));
//
//    //assert(flip_even_bits(8) == 8);
//    //assert(flip_even_bits(9) == 8);
//}