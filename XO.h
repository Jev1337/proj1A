#ifndef XO
#define XO
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>

typedef struct
{
    SDL_Surface * tic_background;
    SDL_Surface * tic_X;
    SDL_Surface * tic_O;
    int tabsuiv[9];
    SDL_Rect pos_premier;
    int joueur;
    int tour;
    TTF_Font *font;
    SDL_Color color;
    char text[1];
    SDL_Rect pos_text;
}tic;

void initialiserTic (tic *t);
void afficherTic(int tabsuivi[], SDL_Surface *ecran);
int atilganer(int tabsuivi[]);
void Resultat(int tabsuivi[], SDL_Surface *ecran, tic t);
int minimax(int tabsuivi[9],int joueur);
void calcul_coup(int tabsuivi[9]);


#endif