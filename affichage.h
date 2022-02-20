#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "gamehead.h"
#include "ninjahubstd.h"

int menu(btndim *BD, btn *B, gameitems *GI, misc *M, menuitems *MI, settingsitems *SI, int *actpos, int *actpos_previous, SDL_Surface *screen);
int setting(btndim *BD,btn *B,pauseitems *PI, menuitems *MI, gameitems *GI, settingsitems *SI,misc *M, int *actpos, int actpos_previous, SDL_Surface *screen);
int credit(btndim *BD,btn *B,misc *M, menuitems *MI, settingsitems *SI, int *actpos, SDL_Surface *screen);
int game(btndim *BD,btn *B,menuitems *MI,gameitems *GI,pauseitems *PI,misc *M, int *actpos, SDL_Surface *screen);
int pause(btndim *BD,btn *B,settingsitems *SI, gameitems *GI, pauseitems *PI, menuitems *MI, misc *M, int *actpos, int *actpos_previous, SDL_Surface *screen);
void show_menu(btndim *BD,btn *B,menuitems *MI, settingsitems *SI, SDL_Surface *screen);
void show_pausemenu(btndim *BD,btn *B,menuitems *MI, gameitems *GI, pauseitems *PI, SDL_Surface *screen);
void show_game(btndim *BD,btn *B,gameitems *GI, SDL_Surface *screen);
void show_credits(btndim *BD,btn *B,menuitems *MI,settingsitems *SI, SDL_Surface *screen);
void show_settings(btndim *BD,btn *B,settingsitems *SI, misc *M,SDL_Surface *screen);

#endif