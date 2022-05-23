//
// Created by nimrod on 17-May-22.
//

#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include "Stack.h"

static Element clone_double(Element double_elem) {
    if (!double_elem) return NULL;
    double *p = malloc(sizeof(double));
    *p = *((double *) double_elem);
    return p;
};

//int main() {
//    Stack s = StackCraete(clone_double, free);
//    for (int i = 0; i <= 10; ++i) {
//        double d = sqrt(i);
//        StackPush(s, &d);
//    }
//
//    while(!StackIsEmpty(s)) {
//        printf("%f\n", *((double *)StackPop(s)));
//    }
//}
