#ifndef EX4_2022_HIST_H
#define EX4_2022_HIST_H

#include <stdbool.h>

typedef void *Element;
typedef struct Hist *Hist;

// An ADT for the Hist object. Such object maintains and unordered set of elements, along with a count for each one.

// Create a new histogram object, with element manipulation functions:
// clone_func - return a pointer to the cloned element.
// free_func - free an element returned by clone_func
// cmp_func - return true if the two elements are equal

Hist HistCreate(Element (*clone_func)(Element),
                void (*free_func)(Element),
                bool (*cmp_func)(Element, Element));

// Destroy a histogram object (along with all its elements)
void HistDestroy(Hist hist);

// Return the number of elements in the hist object
unsigned int HistSize(Hist hist);

// Get the count of element e. If e is not in hist, returns 0.
int HistGetCount(Hist hist, Element e);

// Increment the count of e by one.
// If e is not in hist, create a new entry with a clone of e and a count of 1.
void HistInc(Hist hist, Element e);

// Gets (a clone of) the element at given index.
// If index<0 or index >= HistSize(hist) then NULL is returned.
Element HistGetElement(Hist hist, unsigned int index);

#endif //EX4_2022_HIST_H
