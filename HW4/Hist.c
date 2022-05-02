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

    size_t size;

    Set set;
};

//Static pointers for synchronizing current element clone, cmp and free functions
static Element (*element_clone_func)(Element);

static void (*element_free_func)(Element);

static bool (*element_cmp_func)(Element, Element);

void update_static_set_funcs(Hist hist) {
    element_clone_func = hist->clone_func;
    element_free_func = hist->free_func;
    element_cmp_func = hist->cmp_func;
}

static Element clone_node_func(Element elem_to_clone) {
    if (!elem_to_clone) return NULL;
    Node new_node = calloc(sizeof(struct Node), 1);
    new_node->e = element_clone_func(((Node)elem_to_clone)->e);
    new_node->count = ((Node)elem_to_clone)->count;
    return new_node;
};

static bool cmp_node_func(Element elem1, Element elem2) {
    if(!elem1 || !elem2) return !elem1 && !elem2;
    return element_cmp_func(((Node) elem1)->e, ((Node) elem2)->e);
}

static void free_node_func(Element elem) {
    if(!elem) return;
    element_free_func(((Node) elem)->e);
    free(elem);
}

Hist HistCreate(Element (*clone_func)(Element),
                void (*free_func)(Element),
                bool (*cmp_func)(Element, Element)) {
    Hist hist = calloc(sizeof(struct Hist), 1);
    if (!hist) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Hist));
        exit(-1);
    }
    hist->size = 0;
    hist->clone_func = clone_func;
    hist->free_func = free_func;
    hist->cmp_func = cmp_func;
    update_static_set_funcs(hist);
    hist->set = SetCreate(clone_node_func, free_node_func, cmp_node_func);

    return hist;
}

//Returns Node from hist by Element to compare, NULL when none exists
Node getNodeByElement(Hist hist, Element e) {
    update_static_set_funcs(hist);
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
    update_static_set_funcs(hist);
    SetDestroy(hist->set);
    free(hist);
}

// Return the number of elements in the hist object
unsigned int HistSize(Hist hist) {
    return hist->size;
}

// Get the size of element e. If e is not in hist, returns 0.
int HistGetCount(Hist hist, Element e) {
    Node node = getNodeByElement(hist, e);
    if (node) {
        return node->count;
    }
    return 0;
}

// Increment the size of e by one.
// If e is not in hist, create a new entry with a clone of e and a size of 1.
void HistInc(Hist hist, Element e) {
    update_static_set_funcs(hist);
    Node node = getNodeByElement(hist, e);
    if (node) {
        node->count++;
        return;
    }
    Node new_node = calloc(sizeof(struct Node), 1); //TODO: FIX code duplication with clone_node_func
    if (!new_node) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Hist));
        exit(-1);
    }
    new_node->e = hist->clone_func(e);
    new_node->count = 1;

    SetAdd(hist->set, new_node);
    hist->size++;
}


// Gets (a clone of) the element at given index.
// If index<0 or index >= HistSize(hist) then NULL is returned.
Element HistGetElement(Hist hist, unsigned int index) {
    update_static_set_funcs(hist);
    if (index < 0 || index >= HistSize(hist)) {
        return NULL;
    }

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
