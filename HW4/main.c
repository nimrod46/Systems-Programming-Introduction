//
// Created by nimrod on 27-Apr-22.
//
//תקבל דרך שורת הפקודה עד שני פרמטרים : נתיב )path )של קובץ קלט ונתיב של קובץ הפלט. אם
//        חסר קובץ הפלט, או שקובץ הפלט הינו התו מינוס " -", אז הפלט יכתב ל -stdout .אם חסר קובץ
//        הקלט, או שקובץ הקלט הינו התו מינוס "-", אז הקלט יכתב ל -stdin .אם מספר הארגומנטים גדול
//מדי, או פתיחת הקבצי הקלט/פלט נכשלה, הוציאו הודעת שגיאה ל -stderr וסיימו את התוכנית.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hist.h"

FILE *getSysStreamOrDefByArg(int argc, char *argv[], const char *type, FILE *system_def);


static Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem) + 1);
    strcpy(p, str_elem);
    return p;
};

static bool cmp_str(Element int_elem_1, Element int_elem_2) {
    char *c1 = (char *) int_elem_1;
    const char *c2 = (char *) int_elem_2;
    unsigned int len1 = strlen(c1);
    bool b = strcmp(int_elem_1, int_elem_2) == 0;

    return b;
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    FILE *input = getSysStreamOrDefByArg(argc, argv, "r", stdin);
    FILE *output = getSysStreamOrDefByArg(--argc, ++argv, "w", stdout);

    printf("Started: %d\n", stdin == input);
    Hist hist = HistCreate(clone_str, free, cmp_str);
    char *buf = NULL;
    size_t buf_size;
    while (getline(&buf, &buf_size, input) != EOF) {
        size_t last_idx = strlen(buf) - 1;
        if( buf[last_idx] == '\n' ) {
            buf[last_idx] = '\0';
        }
        HistInc(hist, buf);
    }

    for (int i = 0; i < HistSize(hist); ++i) {
        char *str = HistGetElement(hist, i);
        fprintf(output, "%3d %s\n", HistGetCount(hist, str), str);
    }
    fclose(output);
}

FILE *getSysStreamOrDefByArg(int argc, char *argv[], const char *type, FILE *system_def) {
    if (argc <= 1 || *argv[1] == '-') {
        return system_def;
    }
    FILE *input = fopen(argv[1], type);
    if (!input) {
        fprintf(stderr, "Unable to open '%s'\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }
    return input;
}
