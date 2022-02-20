#ifndef GAMESTRUCTS_H_INCLUDED
#define GAMESTRUCTS_H_INCLUDED
#include "gamehead.h"


typedef struct{

    SDL_Rect menubtns[5];
    SDL_Rect donebtn;
    SDL_Rect resumebtn;
    SDL_Rect settingsbtnreal;
    SDL_Rect fsbtn;

}btndim;

typedef struct{
    SDL_Surface *menubtns_u[5];
    SDL_Surface *menubtns_s[5];
    SDL_Surface *resumebtn[2];
    SDL_Surface *settingsbtnreal[2];
    SDL_Surface *donebtn[2];
    SDL_Surface *fsbtn[3];

    int isselected[9];
}btn;

typedef struct{
    SDL_Surface *background;
    SDL_Surface *credits;
    SDL_Surface *gitbtn_s;
    SDL_Surface *leftarrow;
    SDL_Surface *rightarrow;
    SDL_Surface *btnreset;
    SDL_Surface *rainspr; 
    SDL_Surface *gamename;
    SDL_Rect rainclip[8];
}menuitems;

typedef struct{
    SDL_Surface *gamebackground;
}gameitems;

typedef struct{
    SDL_Surface *pausemenu;
}pauseitems;

typedef struct{
    SDL_Surface *settings;
}settingsitems;

typedef struct{
    Mix_Music *music;
    Mix_Chunk *scratch;
    TTF_Font *font;
    TTF_Font *fontBig;
    int SCREEN_W;
    int SCREEN_H;
    int volume;

}misc;

#endif