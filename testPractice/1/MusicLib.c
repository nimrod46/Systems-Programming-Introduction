#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "MusicLib.h"
#include "../../HW4/Set.h"

struct MusicLib {
    Set set;
    char* (*get_song_name) (const char*);
    char* (*get_song_lyrics) (const char*);
};

Element cpy_str(Element element) {
    const char* str = (char*) element;
    char* des = calloc(strlen(str), sizeof(char));
    strcpy(des, str);
    return des;
}

bool cmp_str(Element element1, Element element2) {
    const char* str1 = (char*) element1;
    const char* str2 = (char*) element2;
    return !strcmp(str1, str2);
}

MusicLib MLCreate(char* (*get_song_name) (const char*), char* (*get_song_lyrics) (const char*)){
    MusicLib musicLib = calloc(sizeof(struct MusicLib), 1);
    if(!musicLib) {
        fprintf(stderr, "Error! Could not allock memoery!");
        exit(1);
    }
    musicLib->set = SetCreate(cpy_str, free, cmp_str);
    musicLib->get_song_name = get_song_name;
    musicLib->get_song_lyrics = get_song_lyrics;
    return musicLib;
}

void MLAdd(MusicLib musicLib, const char* file_name) {
    SetAdd(musicLib->set, file_name);
}


void MLPrintLyrics(MusicLib musicLib, const char* song_name) {
    Element e = SetFirst(musicLib->set);
    while(e) {
        char* next_song_name = musicLib->get_song_name((char* ) e);
        if(!strcmp(next_song_name, song_name)) {
            char * l = musicLib->get_song_lyrics((char* ) e);
            printf("%s\n", l);
            free(l);
            free(next_song_name);
            break;
        }
        free(next_song_name);
        e = SetNext(musicLib->set);
    }
}
