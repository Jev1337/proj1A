#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "gamehead.h"
#include "ninjahubstd.h"

int menu(btn *B, gameitems *GI, misc *M, menuitems *MI, settingsitems *SI, int *actpos, int *actpos_previous, SDL_Surface *screen);
int setting(btn *B,pauseitems *PI, menuitems *MI, gameitems *GI, settingsitems *SI,misc *M, int *actpos, int actpos_previous, SDL_Surface *screen);
int credit(btn *B,misc *M, menuitems *MI, settingsitems *SI, int *actpos, SDL_Surface *screen);
int game(btn *B,menuitems *MI,gameitems *GI,pauseitems *PI,misc *M, int *actpos, SDL_Surface *screen);
int pause(btn *B,settingsitems *SI, gameitems *GI, pauseitems *PI, menuitems *MI, misc *M, int *actpos, int *actpos_previous, SDL_Surface *screen);
void show_menu(btn *B,menuitems *MI, settingsitems *SI, SDL_Surface *screen);
void show_pausemenu(btn *B,menuitems *MI, gameitems *GI, pauseitems *PI, SDL_Surface *screen);
void show_game(btn *B,gameitems *GI, SDL_Surface *screen);
void show_credits(btn *B,menuitems *MI,settingsitems *SI, SDL_Surface *screen);
void show_settings(btn *B,settingsitems *SI, misc *M,SDL_Surface *screen);

#endif