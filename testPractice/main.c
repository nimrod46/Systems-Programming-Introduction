#include <stdlib.h>
#include "MusicLib.h"

//
// Created by nimrod on 30/06/2022.
//
char* get_song_name (const char* f){
    char* s = calloc(sizeof(char), 5);
    s[0] = 'n';
    s[1] = 'a';
    s[2] = 'm';
    s[3] = 'e';
    return s;
}
char* get_song_lyrics (const char* f){
    char* s = calloc(sizeof(char), 6);
    s[0] = 'l';
    s[1] = 'y';
    s[2] = 'r';
    s[3] = 'i';
    s[4] = 'c';
    return s;
}

int main () {

    MusicLib ml = MLCreate(get_song_name, get_song_lyrics);
    MLAdd(ml, "s");
    MLPrintLyrics(ml,"name");
}