
#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include "gamehead.h"




void initcharacter(character *p);
void setcharacter(character *p, character *popt, Uint8* keystate); 
void changedirection (character  *p,character *popt, background *b, int SecOpt);
void afficher_character (character * p, SDL_Surface *screen);
void jump (character * p,btndim *BD, btn *B, gameitems *GI,Ennemi *e, PickUp coin, background *b, SDL_Surface *screen);
void cleancharacter(character *p);


#endif