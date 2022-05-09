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
void initmap(minimap *m, int x)
{
    if (x){
    m->minimap =  IMG_Load("images/Red(LevelOne)minimap.png");
    m->posminimap.x = 400;
    m->posminimap.y = 20;
    m->point = IMG_Load("images/point.png");
    m->temps = time(NULL);;
    m->pospoint.y = 80;
    }
    else{
        m->minimap =  IMG_Load("images/Red(LevelOne)minimap.png");
        m->posminimap.x = 400;
        m->posminimap.y = 20;
        m->point = IMG_Load("images/point.png");
        m->temps = 60;
        m->pospoint.x = 400;
        m->pospoint.y = 80;
        m->temps = time(NULL);
    }
}
void afficherminimap(minimap m, SDL_Surface *zoomable, SDL_Surface *screen)
{
    Uint8 *keystate = SDL_GetKeyState(NULL);
    SDL_Rect zoomMAP;
    SDL_Rect zoomPOINT;
    zoomMAP = m.posminimap;
    zoomPOINT = m.pospoint;
    zoomMAP.y = m.posminimap.y +500;
    zoomPOINT.y = m.pospoint.y +550;
    zoomMAP.x = 0;
    zoomPOINT.x = zoomPOINT.x-20;
    
    
    if (keystate[SDLK_z]){
        SDL_BlitSurface(zoomable, NULL, screen, &zoomMAP); // affichage minimap
        SDL_BlitSurface(m.point, NULL, screen, &zoomPOINT);     // affichage point
    }
    else{
        SDL_BlitSurface(m.minimap, NULL, screen, &m.posminimap); // affichage minimap
        SDL_BlitSurface(m.point, NULL, screen, &m.pospoint);     // affichage point     
    }
}