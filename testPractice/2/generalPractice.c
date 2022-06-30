//
// Created by nimrod on 30/06/2022.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void remove_charr(char s[], char ch) {
    int offset = 0;
    int len = strlen(s);
    for(int i = 0; i < len - offset; i++) {
        while(s[i + offset] == ch) {
            offset++;
        }
        s[i] = s[i + offset];
    }
    s[len - offset] = '\0';
}

int* divided_by(int* s1, unsigned int n1, int* s2, unsigned int n2){
    int* arr = NULL;
    int size = 0;
    for(int* p1 = s1; p1 - s1 < n1; p1++) {
        bool has_div = false;
        for(int* p2 = s2; p2 - s2 < n2; p2++) {
            if(*(p1) % *(p2) == 0) {
                has_div = true;
                break;
            }
        }
        if(!has_div){
            arr = realloc(arr, sizeof(int) * (size+1));
            *(arr +size) = *(p1);
            size++;
        }
    }

    return arr;
}


//int main() {
//    //char c[] = "r123rrr456r";
//    //remove_charr(c, 'r');
//    //printf("%s", c);
//    int s1[] = {1, 10, 5, 4, 21, 49, 24}, s2[] = {2, 3};
//
//    int* arr = divided_by(s1, 7, s2, 2);
//    for (int i = 0; i < 7; ++i) {
//        printf("%d", arr[i]);
//    }
//}
