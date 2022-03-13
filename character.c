
#include "gamehead.h"
#include "character.h"

void initcharacter(character *p){
    p->charsprite[0] = IMG_Load("images/leftsheet.png");
    p->charsprite[1] = IMG_Load("images/rightsheet.png");
    p->direction = 1;
    p->side=-2;
    p->offset.x = 0;
    p->offset.y = 1080-p->clips[p->direction].h;
}

void setcharacter(character *p, SDL_Event event){
    if (event.type == SDL_KEYDOWN)
        {

            if (event.key.keysym.sym == SDLK_LEFT)
            {
                p->side = 0;
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                p->side = 1;
            }

        }
        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                p->side = -1;
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                p->side = -2;
            }
        }
}

void jump (character * p,btndim *BD, btn *B, gameitems *GI, SDL_Surface *screen){
    int i;
    for (i=0; i<=12;i++, p->offset.y-= 30)
    {
        if (p->side == 1 | p->side == -2){
          if (p->offset.x + 10 < 1920 - p->clips[0].w)
              p->offset.x+=10;
        }
        else if (p->side == 0 | p->side == -1){
            if (p->offset.x - 10 > 0)
              p->offset.x-=10;
        }

        show_game(BD, B, GI, screen);
        afficher_character(p,screen);
        SDL_Flip(screen);
    }
    for (i=0; i<=12;i++, p->offset.y+= 30)
    {
               if (p->side == 1 | p->side == -2){
          if (p->offset.x - 10 < 1920 - p->clips[0].w)
              p->offset.x+=10;
        }
        else if (p->side == 0 | p->side == -1){
            if (p->offset.x - 10 > 0)
              p->offset.x-=10;
        }
        show_game(BD, B, GI, screen);
        afficher_character(p,screen);
        SDL_Flip(screen);
    }
}

void changedirection(character *p){
if (p->side == 0)
    {
        if (p->offset.x > 0)
            p->offset.x-=60;
        p->direction--;
        if (p->direction == -1)
            p->direction = 3;
    }
    else if (p->side == 1)
    {
        if (p->offset.x < 1920 - p->clips[0].w)
            p->offset.x+=60;
        p->direction++;
        if (p->direction == 5)
            p->direction = 1;
    }
    else if (p->side == 3){
        
    }
    else if (p->side == -1)
        p->direction = 4;
    else
        p->direction = 0;
}

void afficher_character(character *p, SDL_Surface *screen){
    
    if (p->side >= 0)
        afficher_ecran(p->offset.x, p->offset.y, p->charsprite[p->side], screen, &p->clips[p->direction]);
    else if (p->side == -1)
        afficher_ecran(p->offset.x, p->offset.y, p->charsprite[0], screen, &p->clips[p->direction]);
    else
        afficher_ecran(p->offset.x, p->offset.y, p->charsprite[1], screen, &p->clips[p->direction]);
}