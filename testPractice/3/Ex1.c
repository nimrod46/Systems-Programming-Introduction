//
// Created by nimrod on 30/06/2022.
//


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>




int findocc(const char* s1 , unsigned int n ) {
    int i = 0 ;
    char buff[50]; //this will be long inough for any int..
    sprintf (buff , "%d" , n );
    char *ps1 , *pbuff;

    for ( ; *s1 ; s1++ ) {
        i++;
        for ( ps1 = s1 , pbuff = buff ; *ps1 == *pbuff && *ps1 && *pbuff ; ps1++ , pbuff++ );
        if( !*pbuff )
            return i;
    }
    return -1;

}





char *replace1(const char *sSource, unsigned int nSearch, unsigned int nReplace) {
    unsigned int des_index = findocc(sSource, nSearch);
    unsigned int sSource_size = strlen(sSource);
    unsigned int nSearch_size = 0;
    unsigned int nReplace_size = 0;

    while (nSearch) {
        nSearch_size++;
        nSearch /= 10;
    }

    unsigned int tmp = nReplace;
    while (tmp) {
        nReplace_size++;
        tmp /= 10;
    }

    int source_index = sSource_size - 1;
    unsigned int res_size = nReplace_size + sSource_size - nSearch_size;
    char *res = calloc(res_size + 1, sizeof(char));

    unsigned int i = res_size - 1;
    for (; i > des_index + nSearch_size - 1; i--, source_index--) {
        res[i] = sSource[source_index];
    }
    source_index -= nSearch_size;
    while (nReplace) {
        res[i] = nReplace % 10 + '0';
        i--;
        nReplace /= 10;
    }

    for (; source_index >= 0; i--, source_index--) {
        res[i] = sSource[source_index];
    }
    return res;
}

char *replace(const char *sSource, unsigned int nSearch, unsigned int nReplace) {
    unsigned int des_index = findocc(sSource, nSearch);
    if (des_index == -1) {
        return sSource;
    }
    unsigned int sSource_size = strlen(sSource);
    unsigned int nSearch_size = 0;
    unsigned int nReplace_size = 0;

    while (nSearch) {
        nSearch_size++;
        nSearch /= 10;
    }

    unsigned int tmp = nReplace;
    while (tmp) {
        nReplace_size++;
        tmp /= 10;
    }

    unsigned int res_size = sSource_size + nReplace_size - nSearch_size;
    char *res = calloc(res_size + 1, sizeof(char));

    strncpy(res, sSource, des_index);

    sprintf(res + des_index, "%d", nReplace);

    strcpy(res + des_index + nReplace_size, sSource + des_index + nSearch_size);

    return res;
}

//
//int main() {
//    printf("%s", replace("fd9ds399", 9, 12));
//    return 1;
//}
