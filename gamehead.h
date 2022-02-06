
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




int load_files();
SDL_Surface *load_image(char filename[]);
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest);
void finprog();
int afficher_menu();
int init();
int load_files();
int menu();
void show_menu();
void show_settings();
void show_game();
void show_pausemenu();
void show_credits();
void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen);

#endif // MENU_H_INCLUDED
