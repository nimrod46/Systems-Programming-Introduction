#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//
// Created by nimrod on 30/06/2022.
//
char* compress(const char* s) {
    unsigned int len = strlen(s);
    char *c = NULL;
    for (int i = 0; i < len; ++i) {
        int code = 0;
        if(s[i] > '0' && s[i] < '9') {
            code = s[i] - '0' + 1;
        } else if(s[i] == '\n') {
            code = 11;
        } else if(s[i] == ' ') {
            code = 12;
        }
        c = realloc(c, ((i + 2) >> 1) * sizeof(char));
        c[i >> 1] |= !(i & 1) ? code : code << 4;
    }
    return c;
}

int compressed_strlen(const char* c) {
    int count = 0;
    while(1) {
        if(*c % 16) {
            count++;
        } else {
            break;
        }
        if(*c / 16) {
            count++;
            c++;
        } else {
            break;
        }
    }
    return count;
}


int main() {
    char s[] = "1234  ";
    char *c = compress(s);
    int len = compressed_strlen(c);
    printf("%d\n", len);
    for (int i = 0; i < len / 2; ++i) {
        printf("%x\n", c[i]);
    }
    return 0;
}