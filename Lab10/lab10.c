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
    int size = sizeof(unsigned int) * 8;
    for (int i = 0; i < size; ++i) {
        unsigned int l = n & (1 << (i));
        new = new << 1;
        new = new | (l >> i);
    }
    return new;
}

bool get_bit(unsigned char *arr, unsigned int index) {
    unsigned int array_index = index / 8;
    unsigned int bit_index = index % 7;
    return (1 << bit_index) & arr[array_index];
}

unsigned int create_largest(unsigned int n) {
    unsigned int new = 0;
    unsigned int current_bit_index = sizeof(unsigned int) * 8 - 1;
    for (int i = 0; i < sizeof(unsigned int) * 8; ++i) {
        if (((1 << i) & n)) {
            new |= 1 << current_bit_index ;
            current_bit_index--;
        }
    }
    if(new % 2 != 0) {
        return 0;
    }
    return new;
}


int main() {
    assert(check_bit(0x9, 3));

    assert(even_bits(9) == 1);
    assert(even_bits(8) == 0);

    //"0" = 00110000
    unsigned char arr[40] = "000";
    assert(get_bit(arr, 5));
    assert(get_bit(arr, 12));

    assert(create_largest(12) == (3 << 30));//12 = (1100), 3 = (011)
    assert(create_largest(5) == (3 << 30));//5 = (101)
    assert(create_largest(11) == (7 << 29));//11 = (1011), 7 = (111)
    assert(create_largest(7) == (7 << 29));
    assert(create_largest(0xFFFFFFFF) == 0);
}