#include <stdio.h>

//
// Created by nimrod on 03-Jul-22.
//
void my_cut(FILE* fp, int s, int e) {
    char *buff = NULL;
    size_t buf_size = 0;
    size_t n = 0;
    while((n=getline(&buff, &buf_size, fp)) != EOF){
        int current_index = s;
        if(n <= s) {
            printf("\n");
            continue;
        }
        for(; current_index < n && current_index <= e; current_index++) {
            printf("%c", buff[current_index]);
        }
        if(current_index < n) {
            printf("\n");
        }
    }
}

//int main() {
//    FILE* f= fopen("yesterday.txt", "r");
//    my_cut(f, 2, 10);
//}