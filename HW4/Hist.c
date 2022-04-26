#include "Hist.h"
#include "LinkedList.h"
#include "Set.h"
//
// Created by nimrod on 26-Apr-22.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Node;
struct Node {
    Element e;
    int *count;
};

struct Hist {
    Element (*clone_func)(Element);
    void (*free_func)(Element);
    bool (*cmp_func)(Element, Element);
    LinkedList linkedList;
    Set set;
};

Hist HistCreate(Element (*clone_func)(Element),
                void (*free_func)(Element),
                bool (*cmp_func)(Element, Element)) {
    Hist hist = calloc(sizeof(struct Hist), 1);
    if(!hist) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Hist));
        exit(-1);
    }
    hist->linkedList = LLCreate(clone_func, free_func);
    hist->set = SetCreate(clone_func, free_func, cmp_func);
    hist->clone_func = clone_func;
    hist->free_func = free_func;
    hist->cmp_func = cmp_func;
    return hist;
}

// Destroy a histogram object (along with all its elements)
void HistDestroy(Hist hist) {

}

// Return the number of elements in the hist object
unsigned int HistSize(Hist hist) {
    return LLSize(hist->linkedList);
}

// Get the count of element e. If e is not in hist, returns 0.
int HistGetCount(Hist hist, Element e){
    if (SetIsIn(hist->set, e)) {
        SetNext(hist->set)
    }
    return 0;
}

bool contains(Hist hist, Element e) {
    return
}

// Increment the count of e by one.
// If e is not in hist, create a new entry with a clone of e and a count of 1.
void HistInc(Hist hist, Element e);

// Gets (a clone of) the element at given index.
// If index<0 or index >= HistSize(hist) then NULL is returned.
Element HistGetElement(Hist hist, unsigned int index);