#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include "gamehead.h"

typedef struct{
    SDL_Surface *Q;
    SDL_Surface *QM;
    SDL_Surface *RSurf;
    SDL_Surface *R[3];
    TTF_Font *font;
    int RJ;
    int rand;
}enigme;

int afficher_enigme(enigme *e, SDL_Surface *screen);
int split (const char *txt, char delim, char ***tokens);
void init_enigme(enigme *e, char nomfich[]);
int animer(enigme *e, SDL_Event event);
//void sauvegarder()
//void charger()
#endif