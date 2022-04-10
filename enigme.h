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

void afficher_enigme(enigme *e, SDL_Surface *screen);
int init_enigme(enigme *e, char nomfich[], SDL_Surface *screen);
void animer(enigme *e, SDL_Surface *screen);
//void sauvegarder()
//void charger()
#endif