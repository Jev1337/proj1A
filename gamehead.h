
#ifndef GAMEHEAD_H_INCLUDED
#define GAMEHEAD_H_INCLUDED
#define SCREEN_W 1920
#define SCREEN_H 1080
#define SCREEN_BBP 32
#define TIME_TO_WAIT 0.5 /* wait for one second */

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>
#define TIME_TO_WAIT 0.5 /* wait for one second */

typedef struct{
    SDL_Surface *background;
    SDL_Surface *credits;
    SDL_Surface *quitbtn_u;
    SDL_Surface *quitbtn_s;
    SDL_Surface *creditsbtn_u;
    SDL_Surface *creditsbtn_s;
    SDL_Surface *continuebtn_u;
    SDL_Surface *continuebtn_s;
    SDL_Surface *gitbtn_u;
    SDL_Surface *gitbtn_s;
    SDL_Surface *settingsbtn_u;
    SDL_Surface *settingsbtn_s;
    SDL_Surface *gamenameA;
    SDL_Surface *gamenameB;
    SDL_Surface *leftarrow;
    SDL_Surface *rightarrow;
    int continueselected;
    int settingsselected;
    int creditsselected;
    int quitselected;
    int gitselected;
}menuitems;

typedef struct{
    SDL_Surface *gamebackground;
}gameitems;

typedef struct{
    SDL_Surface *pausemenu;
    SDL_Surface *resumebtn_u;
    SDL_Surface *resumebtn_s;
    SDL_Surface *settingsbtnreal_u;
    SDL_Surface *settingsbtnreal_s;
    int selectedresume;
    int selectedsettingsreal;
}pauseitems;

typedef struct{
    SDL_Surface *donebtn_u;
    SDL_Surface *donebtn_s;
        SDL_Surface *settings;
    int doneselectedsettings;
}settingsitems;

typedef struct{
    Mix_Music *music;
    Mix_Chunk *scratch;
    TTF_Font *font;
    TTF_Font *fontBig;
    int volume;
}misc;

SDL_Surface *load_image(char filename[]);
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest);
void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen);
SDL_Surface * init();
int load_files(menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M);
int menu(gameitems *GI, misc *M, menuitems *MI, settingsitems *SI, int *ccl, clock_t *last, int *actpos, int *actpos_previous, SDL_Surface *screen);
int setting(pauseitems *PI, menuitems *MI, gameitems *GI, settingsitems *SI,misc *M, int *actpos, int actpos_previous, SDL_Surface *screen);
int credit(misc *M, menuitems *MI, settingsitems *SI, int *actpos, SDL_Surface *screen);
int game(menuitems *MI,gameitems *GI,pauseitems *PI,misc *M, int *actpos, SDL_Surface *screen);
int pause(settingsitems *SI, gameitems *GI, pauseitems *PI, menuitems *MI, misc *M, int *actpos, int *actpos_previous, SDL_Surface *screen);
int afficher_menu(menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, SDL_Surface *screen);
void show_menu(menuitems *MI, SDL_Surface *screen);
void show_pausemenu(menuitems *MI, gameitems *GI, pauseitems *PI, SDL_Surface *screen);
void show_game(gameitems *GI, SDL_Surface *screen);
void show_credits(menuitems *MI,settingsitems *SI, SDL_Surface *screen);
void show_settings(settingsitems *SI, misc *M,SDL_Surface *screen);
void finprog(menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, SDL_Surface *screen);
#endif // MENU_H_INCLUDED
