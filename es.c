#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "es.h"

void generate_Clips(SDL_Rect Clips[8], int frames, int frameWidth, int clipWidth, int clipHeight)
{
    int i, w;
    for (w = 0, i = 0; i < frames; i++, w += frameWidth)
    {
        Clips[i].x = w;
        Clips[i].y = 0;
        Clips[i].w = clipWidth;
        Clips[i].h = clipHeight;
    }
}

void initEnnemi(Ennemi *e)
{
    e->pos.x = 900;
    e->pos.y = 1080-484;
    e->pos.w = 300;
    e->pos.h = 484;
    e->col = 0;
    e->animation.spriteSheet[0] = IMG_Load("images/spritesheet/leftsheet.png");
    e->animation.spriteSheet[1] = IMG_Load("images/spritesheet/rightsheet.png");
    e->animation.spriteSheet[2] = IMG_Load("images/spritesheet/leftsheet.png");
    e->animation.frames = 5;
    e->animation.side = 1;
    e->animation.clipLoaded = 0;
    generate_Clips(e->animation.Clips, e->animation.frames, 300, 300, 484);
}

void afficherEnnemi(Ennemi e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.animation.spriteSheet[e.animation.side], &e.animation.Clips[e.animation.clipLoaded], screen, &e.pos);
}
 
void animerEnnemi(Ennemi *e)
{
    e->animation.clipLoaded++;
    if (e->animation.clipLoaded >= e->animation.frames)
        e->animation.clipLoaded = 0; 
}

void initCoin(PickUp *c)
{
    c->pos.x = 1300;
    c->pos.y = 800;
    c->pos.w = 166;
    c->pos.h = 256;
    c->col = 0;
    c->type = 1;
    c->boost = 0;
    c->animation.spriteSheet[0] = IMG_Load("images/spritesheet/coin.png");
    c->animation.frames = 4;
    c->animation.clipLoaded = 0;
    generate_Clips(c->animation.Clips, c->animation.frames, 230, 166, 256);
}

void afficherCoin(PickUp c, SDL_Surface *screen)
{
    SDL_BlitSurface(c.animation.spriteSheet[c.animation.side], &c.animation.Clips[c.animation.clipLoaded], screen, &c.pos);
}

void animerCoin(PickUp *c)
{
    c->animation.clipLoaded++;
    if (c->animation.clipLoaded >= c->animation.frames)
        c->animation.clipLoaded = 0;
}

void deplacer(Ennemi *e)
{
    if (e->animation.side == 1)
    {
        e->pos.x += 50;
        if (e->pos.x >= 1920-433)
            e->animation.side = 2;
    }
    else if (e->animation.side == 2)
    {
        e->pos.x -= 50;
        if (e->pos.x <=  900)
            e->animation.side = 1;
    }
}

int collisionBB(SDL_Rect posp, SDL_Rect pose)
{
    if (posp.x < pose.x + pose.w &&
        posp.x + posp.w > pose.x &&
        posp.y < pose.y + pose.h &&
        posp.h + posp.y > pose.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void freeEnnemie(Ennemi e)
{
    SDL_FreeSurface(e.animation.spriteSheet[0]);
    SDL_FreeSurface(e.animation.spriteSheet[1]);
    SDL_FreeSurface(e.animation.spriteSheet[2]);
    SDL_FreeSurface(e.animation.spriteSheet[3]);
}

void deplacerIA(Ennemi *e, SDL_Rect posPerso);