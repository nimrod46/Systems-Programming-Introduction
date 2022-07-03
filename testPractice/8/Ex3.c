#include <stdio.h>

//
// Created by nimrod on 03-Jul-22.
//
int numOnes(unsigned int n) {
    int count = 0;
    while(n != 0) {
        count += n % 2;
        n /= 2;
    }
    return count;
}

//int main() {
//    printf("%d", numOnes(5));
//}