//
// Created by Nimrod Machlav
// Id: 315230185
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hist.h"
#include "LinkedList.h"
#include "TestHist.h"

/**
 * @param argc array size
 * @param argv array, first element for file name stream, if empty set "argc" to 0
 * @param is_read True if returned stream is read, else false.
 * @return File stream with the name of "argv" if second element in "argv" exists and not equals to "-".
 * Otherwise returns the system default stream based on "is_read" value.
 */
FILE *getFileStreamOrDefByArg(int argc, char *argv[], bool is_read);

static Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem) + 1);
    strcpy(p, str_elem);
    return p;
};

static bool cmp_str(Element int_elem_1, Element int_elem_2) {
    return strcmp(int_elem_1, int_elem_2) == 0;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    test_hist();
    FILE *input = getFileStreamOrDefByArg(--argc, ++argv, true);
    FILE *output = getFileStreamOrDefByArg(--argc, ++argv, false);

    Hist hist = HistCreate(clone_str, free, cmp_str);
    char *buf = NULL;
    size_t buf_size;
    LinkedList linkedList = LLCreate(clone_str, free);
    while (getline(&buf, &buf_size, input) != EOF) {
        size_t last_idx = strlen(buf) - 1;
        if (buf[last_idx] == '\n') {
            buf[last_idx] = '\0';
        }
        HistInc(hist, buf);
        LLAdd(linkedList, LLSize(linkedList), buf);
    }
    free(buf);
    fclose(input);

    while (LLSize(linkedList) != 0) {
        char *str = LLRemove(linkedList, 0);
        fprintf(output, "%3d %s\n", HistGetCount(hist, str), str);
    }

    fclose(output);
    HistDestroy(hist);
    LLDestroy(linkedList);
}


FILE *getFileStreamOrDefByArg(int argc, char *argv[], bool is_read) {
    if (argc <= 0 || *argv[0] == '-') {
        return is_read ? stdin : stdout;
    }
    FILE *input = fopen(argv[0], is_read ? "r" : "w");
    if (!input) {
        fprintf(stderr, "Unable to open '%s'\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }
    return input;
}
