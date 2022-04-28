#include "TestHist.h"
#include "Hist.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static Element clone_int(Element int_elem) {
    int *p = malloc(sizeof(int));
    *p = *((int *) int_elem);
    return p;
};

static bool cmp_int(Element int_elem_1, Element int_elem_2) {
    return *((int *) int_elem_1) == *((int *) int_elem_2);
}

static int hist_size(Hist hist) {
    int c = 0;
    Element e = HistGetElement(hist, 0);
    while (e) {
        e = HistGetElement(hist, c);
        c++;
    }
    return c;
}

static void test_int_set1() {
    Hist hist = HistCreate(clone_int, free, cmp_int);
    assert(HistSize(hist) == 0);
    int i0 = 0, i1 = 1, i7 = 7;

    HistInc(hist, &i0);
    assert(HistSize(hist) == 1);
    assert(HistGetCount(hist, &i0) == 1);

    HistInc(hist, &i7);
    HistInc(hist, &i7);
    assert(HistSize(hist) == 2);
    assert(HistGetCount(hist, &i0) == 2);

    int *first = (int *) HistGetElement(hist, 0);
    int *second = (int *) HistGetElement(hist, 1);
    assert(*first == i0 || *first == i7);
    assert(*second == i0 || *second == i7);
    assert(*first != *second);
    assert(HistGetElement(hist, 2) == NULL);

    HistInc(hist, &i1);
    assert(HistSize(hist) == 3);
    HistDestroy(hist);
}

static void test_int_set2(int n) {
    Hist hist = HistCreate(clone_int, free, cmp_int);
    int k = n;
    for (int i = 0; i < n; i++)
        HistInc(hist, &k);
    assert(HistSize(hist) == 1);
    assert(hist_size(hist) == 1);
    assert(HistGetCount(hist, &k) == n);
    for (int i = 0; i < n; ++i) {
        HistInc(hist, &i);
        assert(HistSize(hist) == i + 1);
        assert(hist_size(hist) == i + 1);
        assert(HistGetCount(hist, &i) == 1);
    }
}

static Element clone_str(Element str_elem) {
    char *p = malloc(strlen(str_elem) + 1);
    strcpy(p, str_elem);
    return p;
};

static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return !strcmp(str_elem_1, str_elem_2);
}

static void test_str_set() {
    Hist hist = HistCreate(clone_str, free, cmp_str);
    assert(set_size(hist) == 0);
    assert(SetIsEmpty(hist));
    SetAdd(hist, "");
    SetAdd(hist, "abc");
    SetAdd(hist, "def");
    assert(set_size(hist) == 3);
    assert(!SetIsEmpty(hist));
    assert(SetIsIn(hist, "abc"));
    assert(SetIsIn(hist, ""));
    assert(!SetIsIn(hist, "ABC"));
    SetRemove(hist, "abc");
    SetRemove(hist, "abc");
    assert(set_size(hist) == 2);
    assert(!SetIsIn(hist, "abc"));
    assert(SetIsIn(hist, ""));
    assert(!SetIsIn(hist, "ABC"));
    assert(!SetIsEmpty(hist));
    HistDestroy(hist)
}

void test_set() {
    test_int_set1();
    test_int_set2(1100);
    test_str_set();
}
