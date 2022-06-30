#include <stdlib.h>
#include "Queue.h"

typedef struct Node *Node;
struct Node {
    Element element;
    Node next;
};

struct Queue {
    Node head;
    Node tail;
    void (*free) (Element);
};

void QueueDestroy(Queue queue){
    Node n = queue->head;
    while(n) {
        queue->free(n->element);
        Node tmp = n->next;
        free(n);
        n = tmp;
    }
    free(queue);
}

Element QueueRemove(Queue queue) {
    if(!queue->head) {
        return NULL;
    }
    Node t = queue->head->element;
    queue->head = queue->head->next;
    return t;
}

void QueueAdd(Queue queue, Element element) {
    Node new = calloc(1, sizeof (struct Node));
    //Check calloc....
    new->element = element;
    if(!queue->head){
        queue->head = new;
        queue->tail = new;
        return;
    }
    queue->tail->next = new;
    queue->tail = new;
}

Queue QueueCreate(void (*free) (Element)){
    Queue queue = calloc(1, sizeof (struct Queue));
    queue->free = free;
    //Check calloc....
    return queue;

}


