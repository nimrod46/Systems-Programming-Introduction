#include <stdio.h>

//
// Created by nimrod on 03-Jul-22.
//
typedef unsigned int uint;
uint compress_uint(char* array, int array_size) {
    unsigned int res = 0;
    for(int i = 0; i < array_size; i++){
        res |= ((array[i] == '1') << i);
    }
    return res;
}

int main() {
    char *arr = "101010111";
    printf("%d", compress_uint(arr, 9));
}