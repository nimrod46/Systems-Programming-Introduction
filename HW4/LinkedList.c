#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node*  Node;
struct Node {
    Element e;
    Node next;
};

struct LinkedList {
    Element (*clone_func)(Element);
    void (*free_func)(Element);
    Node head;
};

LinkedList LLCreate(Element (*clone_func)(Element),
                    void (*free_func)(Element)) {
    LinkedList ll = calloc(sizeof(struct LinkedList), 1);
    if(!ll) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct LinkedList));
        exit(-1);
    }
    ll->clone_func = clone_func;
    ll->free_func = free_func;
    return ll;
}

void LLDestroy(LinkedList ll) {
    while(ll->head) {
        Element e = LLRemove(ll, 0);
        ll->free_func(e);
    }
    free(ll);
}

unsigned int LLSize(LinkedList ll) {
    int n = 0;
    Node node = ll->head;
    while(node) {
        n++;
        node = node->next;
    }
    return n;
}

void LLAdd(LinkedList ll, unsigned int index, Element element) {
    // This is an error
    if(index > LLSize(ll)) {
        fprintf(stderr, "Error in %s/LLAdd: illegal index %u, "
                        "list size is only %u\n\n", __FILE__, index, LLSize(ll));
        exit(-1);
    }

    // Create the new node
    Node new_node = malloc(sizeof(struct Node));
    if(!new_node) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Node));
        exit(-1);
    }
    new_node->e = ll->clone_func(element);

    // If need to place the new node at the top of the list - do it
    if(index == 0) {
        new_node->next = ll->head;
        ll->head = new_node;
    }
        // Otherwise always keep a pointer to the node before, where we are
        // supposed to insert the node and insert it
    else {
        Node prev = ll->head;
        for(unsigned int i=1; i<index; i++, prev=prev->next)
            ;
        new_node->next = prev->next;
        prev->next = new_node;
    }
}

Element LLRemove(LinkedList ll, unsigned int index) {
    if(index == 0) {
        if(ll->head) {
            Element e = ll->head->e;
            Node node = ll->head;
            ll->head = ll->head->next;
            free(node);
            return e;
        }
        return NULL;
    }

    Node prev = ll->head, curr = ll->head->next;
    unsigned int n = 1;

    for(; n!=index && curr; n++, prev=curr, curr=curr->next)
        ;

    if(!curr)
        return NULL;

    Element e = curr->e;
    prev->next = curr->next;
    free(curr);

    return e;
}
