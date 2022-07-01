//
// Created by nimrod on 01/07/2022.
//

#include <stdio.h>

unsigned int bit_diff_count(unsigned int a, unsigned int b) {
    unsigned int diff = a ^ b;
    unsigned int count = 0;
    for (int i = 0; i < 32; ++i) {
        count += diff & 1;
        diff >>= 1;
    }
    return count;
}

void print_hexa1(void *p, int psize) {
    char hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 4; i <= psize * 8; i += 4) {
        unsigned int mask = *(unsigned int *) (p) & (15 << ((psize * 8 - i)));
        mask >>= (psize * 8 - i);
        printf("%c", hex_digits[mask]);
    }
    printf("\n");
}

void print_hexa2(void *p, int psize) {
    char hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    void*s = p;
    for (p += psize - 1; p - s >= 0; --p) {
        printf("%c", hex_digits[*(unsigned char *) p >> 4]);
        printf("%c", hex_digits[*(unsigned char *) p & 15]);
    }
    printf("\n");
}

//int main() {
//    printf("%d\n", bit_diff_count(3, 2));
//    unsigned char c = 10;
//    print_hexa2((void *) (&c), sizeof(c));
//    unsigned int x = 257;
//    print_hexa2((void *) (&x), sizeof(x));
//}