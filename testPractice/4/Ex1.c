//
// Created by nimrod on 01/07/2022.
//

#include <stdbool.h>
#include <stdio.h>

bool isprime(unsigned int u) {
    for(int i = 2; i < u / 2; i ++) {
        if(u % i == 0) {
            return false;
        }
    }
    return true;
}

//int main() {
//    printf("%s\n", isprime(19) ? "true" : "false");
//    printf("%s\n", isprime(16) ? "true" : "false");
//    printf("%s\n", isprime(27) ? "true" : "false");
//    printf("%s\n", isprime(30) ? "true" : "false");
//}