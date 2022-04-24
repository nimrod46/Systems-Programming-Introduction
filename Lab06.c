//
// Created by nimrod on 24-Apr-22.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* read(const char *path) {
    FILE* f_in = fopen(path, "r");
    char *buff = NULL;
    size_t buf_size = 0;
    char* new_str = calloc(1,1);
    while(getline(&buff, &buf_size, f_in) != EOF) {
        new_str = (char *) realloc(new_str, (strlen(new_str) + buf_size + 1) * sizeof (char));
        strcat(new_str, buff);
    }
    return new_str;
}

int main() {
    printf("%s", read("beatles-summary.txt"));
    return 0;
}

