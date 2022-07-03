
#include <stdio.h>

//
// Created by nimrod on 03-Jul-22.
//
unsigned int createLargest(unsigned int n) {
    unsigned int res = 0;
    int ones = 0;
    if (n == 0) {
        return 0;
    }
    while (n != 0) {
        ones += n % 2;
        n /= 2;
    }
    for (int i = 0; i < ones - 1; ++i) {
        res |= (1 << (31 - i));
    }
    res |= 1;
    return res;
}

int main() {
    printf("%u", createLargest(12));
}

