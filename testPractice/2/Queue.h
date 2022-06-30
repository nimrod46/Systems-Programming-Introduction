#ifndef QUEUE_H
#define QUEUE_H

typedef void* Element;
typedef struct Queue *Queue;

Queue QueueCreate(void (*free) (Element));
void QueueDestroy(Queue queue);
void QueueAdd(Queue queue, Element element);
Element QueueRemove(Queue queue);
unsigned int QueueSize(Queue queue);

#endif //QUEUE_H