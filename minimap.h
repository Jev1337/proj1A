#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>

typedef struct
{
    SDL_Surface *minimap; // image minimap
    SDL_Surface *point;   // image point minimap
    SDL_Rect posminimap;  // position minimap
    SDL_Rect pospoint;    // position point minimap
    int temps;
} minimap;
void initmap(minimap *m, int x);
void afficherminimap(minimap m, SDL_Surface *zoomable, SDL_Surface *screen);
void affichertemps(int temps, SDL_Surface *screen, TTF_Font *police);

#endif