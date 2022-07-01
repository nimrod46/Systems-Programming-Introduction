#ifndef MULTISET_H
#define MULTISET_H
#include <stdbool.h>
typedef struct Multiset* Multiset;
typedef void* Element;
Multiset MultisetCreate(bool (*is_equal)(Element, Element), Element (*cpy)(Element), void (*fre)(Element));
void MultisetDestroy(Multiset); // Destructor – deletes a Multiset
void MultisetAdd(Multiset, Element); // Add an element to a Multiset
void MultisetRemove(Multiset, Element); // Remove an element from a Multiset
bool MultisetExists(Multiset, Element); // Checks if an element exists
// The following function returns the number of copies of an element
unsigned int MultisetNumElements(Multiset, Element);
unsigned int MultisetSize(Multiset); // Total number of elements
// Remove one element from the Multiset and return it to the user
Element MultisetPop(Multiset);
#endif