//
// Created by nimrod on 04-Jul-22.
//
#include <stdio.h>

unsigned int npaths_n(unsigned int n1, unsigned int n2) {
    unsigned int t1 = 0, t2 = 0;
    if(n1 - 1 != -1) {
        t1 = npaths_n(n1 - 1, n2);
    }

    if(n2 - 1 != -1) {
        t2 = npaths_n(n1, n2 - 1);
    }

    return (t1 + t2) == 0 ? 1 : t1 + t2;

}

unsigned int npaths(unsigned int N) {


    return npaths_n(N - 1, N - 1);

}

int main() {
    printf("%d",npaths(5));
}