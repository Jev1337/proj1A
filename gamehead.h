#ifndef GAMEHEAD_H_INCLUDED
#define GAMEHEAD_H_INCLUDED
#define SCREEN_W 1920
#define SCREEN_H 1080
#define SCREEN_BBP 32

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL_getenv.h>

int load_files();
SDL_Surface *load_image(char filename[]);
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest);
void finprog();
int afficher_menu();
int init();
int load_files();
int menu();

#endif // MENU_H_INCLUDED
