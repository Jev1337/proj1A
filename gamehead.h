
#ifndef GAMEHEAD_H_INCLUDED
#define GAMEHEAD_H_INCLUDED
#define SCREEN_BBP 32
#define FRAMES_PER_SECOND 22
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>
#include "timer.h"
#include "ninjahubstd.h"
#include "gamestructs.h"
#include "character.h"
#include "init.h"
#include "enigme.h"
#include "affichage.h"







int afficher_menu(btndim *BD,btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, SDL_Surface *screen);
void finprog(btn *B,menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, SDL_Surface *screen);
#endif // MENU_H_INCLUDED
