//
// Created by nimrod on 03-Apr-22.
//

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

void find_divided(const int *arr, int size, int num) {
    for (int i = 0; i < size; ++i) {
        if ((*arr) % num == 0) {
            printf("%d ", *arr);
        }

        arr++;
    }

}

void remove_char(char *str, char char_to_remove) {
    while (*str != '\0') {
        if (*str == char_to_remove) {
            char *p = str;
            while (*(p + 1) != '\0') {
                *p = *(p + 1);
                p++;
            }
            *p = '\0';
        }
        str++;
    }
}

//int main() {
//    setbuf(stdout, NULL);
//
//    int n;
//    printf("Type n: ");
//    scanf("%d", &n);
//    int *arr = malloc(sizeof(int) * n);
//    for (int i = 0; i < n; ++i) {
//        printf("Type next number: ");
//        scanf("%d", arr + i);
//    }
//    find_divided(arr, n, 5);
//
//    char str[] = "abcrgcr";
//    remove_char(str, 'r');
//
//    printf("%s",str);
//
//
//
//
//}

