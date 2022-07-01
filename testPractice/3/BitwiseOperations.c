#include <stdbool.h>
#include <stdio.h>

//
// Created by nimrod on 01/07/2022.
//
bool test_n (unsigned int n){
    unsigned int mask = ~15;
    return !(n & 1) && (n & mask);
}

//int main() {
//    printf("%s\n", test_n(15) ? "true" : "false");
//    printf("%s\n", test_n(16) ? "true" : "false");
//    printf("%s\n", test_n(27) ? "true" : "false");
//    printf("%s\n", test_n(30) ? "true" : "false");
//}