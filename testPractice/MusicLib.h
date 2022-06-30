#ifndef MUSICLIB_H
#define MUSICLIB_H
typedef struct MusicLib *MusicLib;

MusicLib MLCreate(char* (*get_song_name) (const char*),
                  char* (*get_song_lyrics) (const char*));

void MLDestroy(MusicLib musicLib);
void MLAdd(MusicLib musicLib, const char* file_name);
void MLRemove(MusicLib musicLib, const char* song_name);
void MLPrintLyrics(MusicLib musicLib, const char* song_name);
void MLPrintSongNames(MusicLib ml);




#endif //MUSICLIB_H