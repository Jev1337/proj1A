#ifndef NINJAHUBSTD_H_INCLUDED
#define NINJAHUBSTD_H_INCLUDED


#include "gamehead.h"

SDL_Surface *load_image(char filename[]);
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect* clip);
void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen);

#endif // MENU_H_INCLUDED