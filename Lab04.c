//
// Created by nimrod on 27-Mar-22.
//

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

bool gematriacmp(const char* w1, const char* w2) {
    int index = 0;
    int sum1 = 0;
    int sum2 = 0;
    while(w1[index] != '\0') {
        sum1 += tolower(w1[index]) - 'a' + 1;
        index++;
    }
    index = 0;
    while(w2[index] != '\0') {
        sum2 += tolower(w2[index]) - 'a' + 1;
        index++;
    }
    return sum1 == sum2;
}

void rcopy(char* destination, const char* source) {
    int last_index = 0;
    while(source[last_index + 1] != '\0') {
        last_index++;
    }
    for (int i = last_index; i >= 0; --i) {
        destination[last_index - i] = source[i];
    }
}

int main() {
    bool b = gematriacmp("Abcb", "abcaa");
    printf("%s\n", b ? "true": "false");

    char arr[7];
    rcopy(arr, "1234456");
    for (int i = 0; i < 7; ++i) {
        printf("%c\n", arr[i]);
    }
    return 0;
}
