//
// Created by nimrod on 27-Apr-22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hist.h"

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
    FILE *input = getFileStreamOrDefByArg(argc, argv, true);
    FILE *output = getFileStreamOrDefByArg(--argc, ++argv, false);

    printf("Started: %d\n", stdin == input);
    Hist hist = HistCreate(clone_str, free, cmp_str);
    char *buf = NULL;
    size_t buf_size;
    while (getline(&buf, &buf_size, input) != EOF) {
        size_t last_idx = strlen(buf) - 1;
        if (buf[last_idx] == '\n') {
            buf[last_idx] = '\0';
        }
        HistInc(hist, buf);
    }
    free(buf);
    fclose(input);

    for (int i = 0; i < HistSize(hist); ++i) {
        char *str = HistGetElement(hist, i);
        fprintf(output, "%3d %s\n", HistGetCount(hist, str), str);
    }
    fclose(output);
}

FILE *getFileStreamOrDefByArg(int argc, char *argv[], bool is_read) {
    if (argc <= 1 || *argv[1] == '-') {
        return is_read ? stdin : stdout;
    }
    FILE *input = fopen(argv[1], is_read ? "r" : "w");
    if (!input) {
        fprintf(stderr, "Unable to open '%s'\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }
    return input;
}
