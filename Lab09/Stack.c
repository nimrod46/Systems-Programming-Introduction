#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

//
// Created by nimrod on 17-May-22.
//
struct Stack {
    Element elements[1024];
    int index;

    Element (*cpy)(Element);

    void (*fre)(Element);
};

Stack StackCraete(Element (*cpy)(Element), void (*fre)(Element)) {
    Stack stack = malloc(sizeof(struct Stack));
    stack->index = -1;
    stack->cpy = cpy;
    stack->fre = fre;
}

void StackDestroy(Stack stack) {
    for (int i = 0; i < stack->index; ++i) {
        stack->fre(stack->elements[i]);
    }
    free(stack);
}

void StackPush(Stack stack, Element e) {
    if(stack->index == 1023) {
        fprintf(stderr, "Stack overflow error!");
        exit(1);
    }
    stack->index = stack->index+1;
    stack->elements[stack->index] = stack->cpy(e);
}

Element StackPop(Stack stack) {
    if(stack->index == -1) {
        return NULL;
    }
    Element e = stack->elements[stack->index];
    stack->index = stack->index-1;
    return e;
}

Element StackTop(Stack stack) {
    if(stack->index == -1) {
        return NULL;
    }
    Element e = stack->elements[stack->index];
    return stack->cpy(e);
}

bool StackIsEmpty(Stack stack) {
    return stack->index == -1;
}
