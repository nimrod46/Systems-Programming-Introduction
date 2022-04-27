//
// Created by nimrod on 26-Apr-22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hist.h"
#include "Set.h"

typedef struct Node *Node;
struct Node {
    Element e;
    int count;
};

struct Hist {
    Element (*clone_func)(Element);

    void (*free_func)(Element);

    bool (*cmp_func)(Element, Element);

    unsigned int size;
    Set set;
};

static Element clone_node_func(Node node_elem) {
    if (!node_elem) return NULL;
    Node new_node = malloc(sizeof(struct Node));
    char *p = malloc(strlen(node_elem->e) + 1);
    strcpy(p, node_elem->e);
    new_node->e = p;
    new_node->count = node_elem->count;
    return new_node;
};

Hist HistCreate(Element (*clone_func)(Element),
                void (*free_func)(Element),
                bool (*cmp_func)(Element, Element)) {
    Hist hist = calloc(sizeof(struct Hist), 1);
    if (!hist) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Hist));
        exit(-1);
    }
    //hist->linkedList = LLCreate(clone_func, free_func);
    hist->size = 0;
    hist->set = SetCreate(clone_node_func, free_func, cmp_func);
    hist->clone_func = clone_func;
    hist->free_func = free_func;
    hist->cmp_func = cmp_func;
    return hist;
}

Node getElement(Hist hist, Element e) {
    Node nextNode = SetFirst(hist->set);
    while (nextNode) {
        if (hist->cmp_func(e, nextNode->e)) {
            return nextNode;
        }
        nextNode = SetNext(hist->set);
    }
    return NULL;
}

// Destroy a histogram object (along with all its elements)
void HistDestroy(Hist hist) {

}

// Return the number of elements in the hist object
unsigned int HistSize(Hist hist) {
    return hist->size;
}

// Get the size of element e. If e is not in hist, returns 0.
int HistGetCount(Hist hist, Element e) {
    Node node = getElement(hist, e);
   if(node) {
       return node->count;
   }
    return 0;
}

bool contains(Hist hist, Element e) {
    return SetIsIn(hist->set, e);
}

// Increment the size of e by one.
// If e is not in hist, create a new entry with a clone of e and a size of 1.
void HistInc(Hist hist, Element e){
    Node node = getElement(hist, e);
    if(node) {
        node->count++;
        return;
    }
    Node new_node = malloc(sizeof(struct Node));
    new_node->e = hist->clone_func(e);
    new_node->count = 1;
    SetAdd(hist->set, new_node);
    hist->size++;
}


// Gets (a clone of) the element at given index.
// If index<0 or index >= HistSize(hist) then NULL is returned.
Element HistGetElement(Hist hist, unsigned int index) {
//    if(index<0 || index >= HistSize(hist)) {
//        return NULL;
//    }

    Node nextNode = SetFirst(hist->set);
    int n = 0;
    while (nextNode) {
        if (index == n) {
            return hist->clone_func(nextNode->e);
        }
        nextNode = SetNext(hist->set);
        n++;
    }
    return NULL;




}

