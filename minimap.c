#include "minimap.h"

void affichertemps(int temps, SDL_Surface *screen) // temps compteur
{

    TTF_Font *police = NULL;
    police = TTF_OpenFont("fonts/Urusans.TTF", 40);
    SDL_Color couleur = {255, 255, 255};
    SDL_Rect postemps;
    postemps.x = 0;
    postemps.y = 0;
    char s[20]; // pour mettre "temps:"
    sprintf(s, "Temps: %d", temps);
    SDL_Surface *txt;
    txt = TTF_RenderText_Blended(police, s, couleur);
    SDL_BlitSurface(txt, NULL, screen, &postemps); // affichage temps
}
void initmap(minimap *m)
{
    
    m->minimap = IMG_Load("images/11minimap.png");
    m->posminimap.x = 400;
    m->posminimap.y = 20;
    m->point = IMG_Load("images/point.png");
    m->pospoint.x = 400;
    m->pospoint.y = 80;
    m->temps = 60;
}
void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.minimap, NULL, screen, &m.posminimap); // affichage minimap
    SDL_BlitSurface(m.point, NULL, screen, &m.pospoint);     // affichage point
}