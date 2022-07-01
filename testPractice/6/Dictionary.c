//#include "BsTree.h"
//#include <string.h>
//#include <malloc.h>
//#include "Dictionary.h"
//
//struct Dictionary {
//    BSTree bsTree;
//};
//
//typedef struct Item* Item;
//
//
//struct Item {
//    char* word;
//    char* meaning;
//};
//
//bool is_greater(Element e1, Element e2) {
//    Item t1 = (Item) e1;
//    Item t2 = (Item) e2;
//    return strcmp(t1->word, t2->word) > 0;
//
//}
//
//Dictionary DictionaryCreate() {
//    Dictionary dict = malloc(sizeof(struct Dictionary));
//    dict->bsTree = BSTCreate(is_greater);
//    return dict;
//
//}
//
//bool DictionaryAddWord(Dictionary dictionary, const char* word, const char* meaning) {
//    if(BSTSearchNode(dictionary->bsTree, word)) {
//        return false;
//    }
//    Item item = malloc(sizeof(struct Item));
//    item->word = strdup(word);
//    item->meaning = strdup(meaning);
//    BSTAddNode(dictionary->bsTree, item);
//    return true;
//}