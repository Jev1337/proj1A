#include "gamehead.h"
#include "character.h"

void initcharacter(character *p){
    p->charsprite[0] = IMG_Load("images/leftsheet.png");
    p->charsprite[1] = IMG_Load("images/rightsheet.png");
    p->direction = 1;
    p->side=-2;
    p->offset.x = 0;
    p->offset.y = 1080-p->clips[p->direction].h;
    p->offset.w = 300;
    p->offset.h = p->clips[p->direction].h;
    p->speed =60;
    p->score = 0;
}

void setcharacter(character *p, Uint8* keystate){
    //Mix_Chunk *run;
    //run = Mix_LoadWAV("sounds/running.wav");
    if (keystate[SDLK_LSHIFT])
            {
                if(p->speed < 100)
                p->speed += 10;
            }
            if (keystate[SDLK_RSHIFT])
            {
                if(p->speed > 0)
                p->speed -= 10;
            }
//if (keystate[SDLK_LEFT] || keystate[SDLK_RIGHT])
//Mix_PlayChannel(2,run, 0);

            if (keystate[SDLK_LEFT])
            {
                p->side = 0;
            }
            else  if (p->side == 0)
            {
                p->side = -1;
                //Mix_Pause(-1);
            }
            if (keystate[SDLK_RIGHT])
            {
                p->side = 1;
            } else if (p->side == 1)
            {
                p->side = -2;
               // Mix_Pause(-1);
                
            }
    
}

void jump (character * p,btndim *BD, btn *B, gameitems *GI, Ennemi *e,PickUp coin ,SDL_Surface *screen){
    int i,j;
    Mix_Chunk *jump = Mix_LoadWAV("sounds/jump.wav");;
    Mix_PlayChannel(1,jump, 0);
    for (j=10,i=0; i<=12;i++, j+=3,p->offset.y-= j)
    {
        if (p->side == 1 | p->side == -2){
          if (p->offset.x + 10 < 1920 - p->clips[0].w)
              p->offset.x+=15;
        }
        else if (p->side == 0 | p->side == -1){
            if (p->offset.x - 10 > 0)
              p->offset.x-=15;
        }

        show_game(BD, B, GI, screen);
        afficher_character(p,screen);
        afficherEnnemi(*e, screen);
        afficher_ecran(1300,800,coin.animation.spriteSheet[0],screen, &coin.animation.Clips[coin.animation.clipLoaded]);
        SDL_Flip(screen);
        SDL_Delay(16);
        
    }
    for (j=10,i=0; i<=12;i++, j+=3,p->offset.y+= j)
    {
               if (p->side == 1 | p->side == -2){
          if (p->offset.x - 10 < 1920 - p->clips[0].w)
              p->offset.x+=15;
        }
        else if (p->side == 0 | p->side == -1){
            if (p->offset.x - 10 > 0)
              p->offset.x-=15;
        }
        show_game(BD, B, GI, screen);
        afficher_character(p,screen);
        afficherEnnemi(*e, screen);
        afficher_ecran(1300,800,coin.animation.spriteSheet[0],screen, &coin.animation.Clips[coin.animation.clipLoaded]);
        SDL_Flip(screen);
        SDL_Delay(16);
    }
}

void changedirection(character *p){
if (p->side == 0)
    {
        
        if (p->offset.x > 0)
            p->offset.x-=p->speed;
        p->direction--;
        if (p->direction == -1)
            p->direction = 3;
    }
    else if (p->side == 1)
    {
        if (p->offset.x < 1920 - p->clips[0].w)
            p->offset.x+=p->speed;
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

void cleancharacter(character *p){
    SDL_FreeSurface(p->charsprite[0]);
    SDL_FreeSurface(p->charsprite[1]);
}