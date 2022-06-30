#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Created by nimrod on 30/06/2022.
//
unsigned int longest_line(const char* fname){
    FILE* f = fopen(fname, "r");
    char c;
    unsigned int count = 0;
    unsigned int max_count = 0;
    while((c = fgetc(f)) != EOF) {
        if(c != '\n'){
            count++;
        } else {
            if(max_count < count) {
                max_count = count;
            }
            count = 0;
        }
    }
    fclose(f);
    return max_count;
}

unsigned int num_items(const char* str, char delimiter) {
    unsigned int counter = 1;
    while(*str) {
        if(*(str++) == delimiter) {
            counter++;
        }
    }
    return counter;
}

char** split1(const char* str, char delimiter) {
    unsigned int length = num_items(str, delimiter);
    unsigned int str_len = strlen(str);
    char** arr = calloc(length, sizeof(int));
    char ** res = arr;
    char* arg = calloc(str_len, sizeof(char));
    *arr = arg;
    arr++;
    while(*str) {
        if(*(str) == delimiter) {
            str++;
            arg = calloc(str_len, sizeof(char));
            *arr = arg;
            arr++;
        }
        *arg = *str;
        arg++;
        str++;
    }
    return res;
}

char** split2(const char* str, char delimiter) {
    unsigned int length = num_items(str, delimiter);
    char** arr = calloc(length, sizeof(char*));
    const char* p;
    unsigned int size = 0;
    for(p = str; *p ; p++){
        if(*p == delimiter) {
            arr[size] = calloc(p - str + 1, sizeof(char));
            strncpy(arr[size], str, p - str);
            str = p + 1;
            size++;
        }
    }
    arr[size] = calloc(p - str, sizeof(char));
    strncpy(arr[size], str, p - str);

    return arr;
}

int main () {
    //printf("%d", longest_line("C:\\Users\\nimrod\\Documents\\GitHub\\Systems-Programming-Introduction\\cmake-build-debug\\.ninja_log"));
    //printf("nu,: %d", num_items("Hello:World",':'));
    unsigned int len = num_items(":Hello:World",':');
    printf("num: %d\n", len);
    char** arr = split2("k:Hello:World",':');
    for (int i = 0; i < len; ++i) {
        printf("%s\n", arr[i]);
    }
}
