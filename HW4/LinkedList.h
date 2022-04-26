#ifndef LINKEDLIST_h
#define LINKEDLIST_h

// ADT Linked list type - an ordered list of elements

typedef void* Element;
typedef struct LinkedList* LinkedList;

// Given a function for cloning, and for freeing an element, returns a handle
// To an empty linked list.
LinkedList LLCreate(Element (*clone_func)(Element),
                    void (*free_func)(Element));

// Destroys a list, along with applying free_func to all its elements
void LLDestroy(LinkedList ll);

// Returns the number of elements in the list
unsigned int LLSize(LinkedList ll);

// Adds a (clone of) element e at location index (between 0 to LLSize()).
// Use index=0 to insert at the beginning of the list, index=1 to insert between
// the first and second elements, and index=LLSize() to insert after the last
// element.
void LLAdd(LinkedList ll, unsigned int index, Element element);

// Remove and return an element from the list (index between 0 to LLSize-1),
// Use index=0 for the first element, and index=LLSize-1 for the last element.
Element LLRemove(LinkedList ll, unsigned int index);

#endif
