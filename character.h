
#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include "gamehead.h"


typedef struct{
    SDL_Surface *charsprite[2];
    int direction;
    int side;
    SDL_Rect clips[5];
    SDL_Rect offset;
}character;


void initcharacter(character *p);
void setcharacter(character *p, SDL_Event event);
void changedirection (character  *p);
void afficher_character (character * p, SDL_Surface *screen);
void jump (character * p,btndim *BD, btn *B, gameitems *GI, SDL_Surface *screen);


#endif