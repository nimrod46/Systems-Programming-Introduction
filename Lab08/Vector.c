//
// Created by nimrod on 12-May-22.
//
#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

struct Vector {
    int *ints;
    Vector_Size size;

};

Vector VectorCreate(Vector_Size size) {
    Vector v = calloc(sizeof(struct Vector), 1);
    if (!v) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Vector));
        exit(0);
    }
    v->size = size;

    v->ints = calloc(sizeof(int), size);
    if (!v->ints) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(int) * size);
        exit(0);
    }
    return v;
}

void VectorDestroy(Vector vector) {
    free(vector->ints);
    free(vector);
}

int VectorGet(Vector vector, unsigned int index) {
    return vector->ints[index];
}

void VectorSet(Vector vector, unsigned int index, int element) {
    vector->ints[index] = element;

}
