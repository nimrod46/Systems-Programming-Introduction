#include <stdio.h>
#include <ctype.h>

char my_toupper(char c) {
    int diff = 'A' - 'a';
    if (islower(c)) {
        return c + diff;
    }
    return c;
}

//void main() {
//    setbuf(stdout, NULL);
//    char c;
//    int chars[26] = {0};
//    printf("Enter text: ");
//    while ((c = getchar()) != EOF && c != '\n') {
//        chars[my_toupper(c) - 'A']++;
//    }
//
//    for (int i = 0; i < 26; ++i) {
//        printf("%c      %d\n", 'A' + i, chars[i]);
//    }
//}
