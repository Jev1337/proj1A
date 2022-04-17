#ifndef ES
#define ES
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
    SDL_Surface *spriteSheet[3]; // 0: dead 1: right 2:left
    SDL_Rect Clips[8];
    int side; // 1: right 2: left 0: dead
    int frames;
    int clipLoaded;
} animation;

typedef struct
{
    SDL_Rect pos;
    animation animation;
    int col; // 0: non colusion 1: colusion
} Ennemi;

typedef struct
{
    SDL_Rect pos;
    animation animation;
    int col;
    int type;  // 1: coin 2: boost
    int boost; // 0: no boost 1: speed 2: health
} PickUp;

void generate_Clips(SDL_Rect Clips[8], int frames, int frameWidth, int clipWidth, int clipHeight);

void initEnnemi(Ennemi *e);
void afficherEnnemi(Ennemi e, SDL_Surface *screen);
void animerEnnemi(Ennemi *e);
void deplacer(Ennemi *e);

void initCoin(PickUp *c);
void afficherCoin(PickUp c, SDL_Surface *screen);
void animerCoin(PickUp *c);

int collisionBB(SDL_Rect posp, SDL_Rect pose);
void deplacerIA(Ennemi *e, SDL_Rect posPerso);

void freeEnnemie(Ennemi e);
#endif /* ES */
