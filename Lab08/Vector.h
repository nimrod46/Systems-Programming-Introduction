//
// Created by nimrod on 12-May-22.
//

#ifndef SYSTEMS_PROGRAMMING_INTRODUCTION_VECTOR_H
#define SYSTEMS_PROGRAMMING_INTRODUCTION_VECTOR_H

#endif //SYSTEMS_PROGRAMMING_INTRODUCTION_VECTOR_H

typedef struct Vector *Vector;
typedef unsigned int Vector_Size;

Vector VectorCreate(Vector_Size size);

void VectorDestroy(Vector vector);

int VectorGet(Vector vector, unsigned int index);

void VectorSet(Vector vector, unsigned int index, int element);
