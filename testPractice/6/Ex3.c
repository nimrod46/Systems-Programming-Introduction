#include <stdio.h>
#include <stdbool.h>

//
// Created by nimrod on 01/07/2022.
//
int find_missing1(const int *array, int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += i;
    }

    for (int i = 0; i < n; i++) {
        sum -= array[i];
    }

    return sum;
}

int find_missing2(const int *array, int n) {
    int missing = 0;
    for (int i = 0; i < n; i++) {
        missing ^= array[i];
    }

    return missing;
}

bool is_permutation(const char *s1, const char *s2) {
    int difference[26] = {0};
    int i;
    while (*s1) {
        difference[*(s1++) - 'a']++;
    }
    while (*s2) {
        difference[*(s2++) - 'a']--;
    }
    for (i = 0; i < 26; i++) {
        if (difference[i] != 0)
            return false;
    }
    return true;
}


//int main() {
//    int array[15] = {0, 1, 10, 9, 15, 2, 13, 5, 7, 11, 3, 4, 14, 8, 6};
//
//    printf("%d\n", find_missing2(array, 15));
//
//    char *c1 = "you";
//    char *c2 = "you";
//    printf("%s\n", is_permutation(c1, c2) ? "true" : "false");
//}