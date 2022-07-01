//
// Created by nimrod on 01/07/2022.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Multiset.h"

bool is_equal(Element e1, Element e2) {
    char *c1 = e1;
    char *c2 = e2;
    return !strcmp(c1, c2);
}

Element cpy(Element e) {
    char *src = e;
    char *dst = calloc(strlen(src) + 1, sizeof(char));
    strcpy(dst, src);
    return dst;
}

void fre (Element e) {
    free(e);
}
//int main() {
//    char str[5]  = "1234";
//    char str1[5]  = "123 4";
//    char*s = cpy(str);
//    printf("%s\n", s);
//    printf("%d\n", is_equal(s, str1));
//    fre(s);
//
//
//    Multiset ms = MultisetCreate(is_equal, cpy, fre);
//    char command[7] = "";
//    char item[32] = "";
//    scanf("%s %s", command, item);
//    while(strcmp(command,"STOP") != 0) {
//        if(strcmp(command, "ADD") == 0) {
//            MultisetAdd(ms, item);
//        } else if(strcmp(command, "REMOVE") == 0){
//            if(!MultisetExists(ms, item)) {
//                printf("Error: no %s in the list", item);
//            } else {
//                MultisetRemove(ms, item);
//            }
//        }
//        scanf("%s %s", command, item);
//    }
//
//}