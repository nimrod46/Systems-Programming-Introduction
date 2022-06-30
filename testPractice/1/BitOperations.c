//
// Created by nimrod on 30/06/2022.
//

#include <stdio.h>


unsigned int switch_pairs(unsigned int n) {
    unsigned int x = n & 0xCCCCCCCC;
    unsigned int y = n & 0x33333333;
    return (x >> 2) | (y << 2);
}


unsigned int switch_m_bits(unsigned int n, unsigned int m) {
    unsigned int mask = (1 << m) - 1;
    unsigned int lower_m_bits = n & mask;
    unsigned int upper_m_bits = n & (mask << (32 - m));
    unsigned int reset_mask = ~(mask | (mask << (32 - m)));
    n = reset_mask & n;
    return n | (lower_m_bits << (32 - m)) | (upper_m_bits >> (32 - m));

}

unsigned int switch_ends (unsigned int n, unsigned int i) {
    unsigned int mask1 = (1 << i) - 1;
    unsigned int mask2 = mask1 << (32-i);
    unsigned int mask3 = ~(mask1 | mask2);
    return ((n & mask1) << (32-i)) | ((n & mask2) >> (32-i)) | (n & mask3);
}


void print_octal2(unsigned int n) {
    for(int i=30; i>=0; i-=3) {
        unsigned char x = ((n >> i) & 0x7);
        printf("%d", x);
    }
    printf("\n");
}

//int main() {
//    printf("%u\n", switch_m_bits(142, 3));
//    printf("%u\n", switch_ends(142, 3));
//
//    print_octal2(10);
//}