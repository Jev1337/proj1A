#ifndef NINJAHUBSTD_H_INCLUDED
#define NINJAHUBSTD_H_INCLUDED


#include "gamehead.h"

typedef struct{
    SDL_Surface *image;//background
    SDL_Surface *imageM;//masque
    SDL_Rect posimage;//position background
    SDL_Rect posmask;
    
}background;

typedef struct{
    SDL_Surface *charsprite[2];
    int direction; //Numero Image 
    int side; // Direction Gauche Droite Haut Bas
    SDL_Rect clips[5];
    SDL_Rect offset;
    int health;
    int speed;
}character;
int split (const char *txt, char delim, char ***tokens);
SDL_Surface *load_image(char filename[]);
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect* clip);
void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen);

#endif // MENU_H_INCLUDED