#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED
#include "gamehead.h"


void init_bg(background *b);
SDL_Color GetPixel (SDL_Surface* pSurface,int x,int y);
int collisionPP( SDL_Rect p, SDL_Surface * Masque);
#endif
