#include <stdbool.h>

#ifndef BSTREE_H
#define BSTREE_H
typedef struct BSTree* BSTree;
typedef void* Element;
BSTree BSTCreate(bool (*is_greater)(Element, Element));
void BSTDestroy(BSTree);
BSTree BSTAddNode(BSTree, Element);
BSTree BSTRemoveNode(BSTree, Element);
bool BSTSearchNode(BSTree, Element);
Element* BSTinorder(BSTree);
#endif


#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Dictionary* Dictionary;
Dictionary DictionaryCreate();
void DictionaryDestroy(Dictionary);
bool DictionaryAddWord(Dictionary, const char* word, const char* meaning);
bool DictionaryRemoveWord(Dictionary, const char* word);
const char* DictionaryFindMeaning(Dictionary, const char* word);
int FindWordsBeginWith(Dictionary dictionary, const char* prefix, const char* result[]);
int DictionarySize(Dictionary dictionary);

#endif