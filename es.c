
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "es.h"

/**
 * @file es.c
 */

/**
 * @brief To generate clips for animation.
 * @param Clips to fill it up with cordinate of the spritesheet animation.
 * @param frames for how much frames in the animation.
 * @param frameWidth for width between each frame.
 * @param clipWidth for all the frames width.
 * @param clipHeight for all the frames height.
 * @return Nothing
 */

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

/**
 * @brief To initialise Ennemi.
 * @param e the ennemi to initialise.
 * @return Nothing
 */

void initEnnemi(Ennemi *e)
{
    e->pos.x = 900;
    e->pos.y = 1080-484;
    e->pos.w = 300;
    e->pos.h = 484;
    e->col = 0;
    e->animation.spriteSheet[0] = IMG_Load("images/leftsheet.png");
    e->animation.spriteSheet[1] = IMG_Load("images/rightsheet.png");
    e->animation.frames = 5;
    e->animation.side = 1;
    e->animation.clipLoaded = 0;
    generate_Clips(e->animation.Clips, e->animation.frames, 182, 182, 320);
    e->attack = 0; // new
    e->attackAnimation.spriteSheet[0] = IMG_Load("images/attack_left.png");
    e->attackAnimation.spriteSheet[1] = IMG_Load("images/attack_right.png");
    e->attackAnimation.frames = 5;
    e->attackAnimation.side = 1;
    e->attackAnimation.clipLoaded = 0;
    generate_Clips(e->attackAnimation.Clips, e->animation.frames, 320, 300, 320);
}
/**
 * @brief To show Ennemi.
 * @param e the ennemi to show.
 * @param screen the screen to show the ennemi in.
 * @return Nothing
 */
void afficherEnnemi(Ennemi e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.animation.spriteSheet[e.animation.side], &e.animation.Clips[e.animation.clipLoaded], screen, &e.pos);
}

/**
 * @brief To animate Ennemi.
 * @param e the ennemi to animate.
 * @return Nothing
 */
void animerEnnemi(Ennemi *e)
{
    e->animation.clipLoaded++;
    if (e->animation.clipLoaded >= e->animation.frames)
        e->animation.clipLoaded = 0;
}

/**
 * @brief To init coin.
 * @param c the coin to init.
 * @return Nothing
 */
void initCoin(PickUp *c)
{
    c->pos.x = 1300;
    c->pos.y = 800;
    c->pos.w = 166;
    c->pos.h = 256;
    c->col = 0;
    c->type = 1;
    c->boost = 0;
    c->animation.spriteSheet[0] = IMG_Load("images/coin.png");
    c->animation.frames = 4;
    c->animation.clipLoaded = 0;
    generate_Clips(c->animation.Clips, c->animation.frames, 230, 166, 256);
}

/**
 * @brief To show coin.
 * @param c the coin to show.
 * @param screen the screen to show the ennemi in.
 * @return Nothing
 */
void afficherCoin(PickUp c, SDL_Surface *screen)
{
    SDL_BlitSurface(c.animation.spriteSheet[c.animation.side], &c.animation.Clips[c.animation.clipLoaded], screen, &c.pos);
}

/**
 * @brief To animate coin.
 * @param c the coin to animate.
 * @return Nothing
 */

void animerCoin(PickUp *c)
{
    c->animation.clipLoaded++;
    if (c->animation.clipLoaded >= c->animation.frames)
        c->animation.clipLoaded = 0;
}

/**
 * @brief To move the ennemi.
 * @param e the ennemi to move.
 * @return Nothing
 */
void deplacer(Ennemi *e)
{
    if (e->animation.side == 1)
    {
        e->pos.x += 50;
        if (e->pos.x >= 1920)
            e->animation.side = 0;
        animerEnnemi(e);
    }
    else if (e->animation.side == 0)
    {
        e->pos.x -= 50;
        if (e->pos.x <= 400)
            e->animation.side = 1;
        animerEnnemi(e);
    }
}
/**
 * @brief To detect if there was a collusion or not between the ennemi and main character.
 * @param posp the player pos.
 * @param pose the enemie pos.
 * @return if collusion return 1 if not return 0.
 */
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

/**
 * @brief free all the spritesheet from processeur
 * @param e to get all the spritesheet from the enemie
 * @return Nothing
 */

void freeEnnemie(Ennemi e)
{
    SDL_FreeSurface(e.animation.spriteSheet[0]);
    SDL_FreeSurface(e.animation.spriteSheet[1]);
}

void deplacerIA(Ennemi *e, SDL_Rect posPerso)
{
    int diff = e->pos.x - posPerso.x;
    if (diff > 100 && diff < 200 && e->pos.x >= 400)
    {
        e->pos.x -= 15;
        e->animation.side = 0;
        e->attack = 0;
        animerEnnemi(e);
    }
    else if (diff < -200 && diff > -400 && e->pos.x <= 1920)
    {
        e->pos.x += 15;
        e->animation.side = 1;
        e->attack = 0;
        animerEnnemi(e);
    }
    else if (diff >= 50 && diff <= 100)
    {
        e->animation.clipLoaded = 0;
        e->attackAnimation.side = 0;
        e->attack = 1;
        return;
    }
    else if (diff <= -150 && diff >= -200)
    {
        e->animation.clipLoaded = 0;
        e->attackAnimation.side = 1;
        e->attack = 1;
        return;
    }
    else
    {
        e->attack = 0;
        deplacer(e);
    }
}

// new
void afficherAttack(Ennemi e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.attackAnimation.spriteSheet[e.attackAnimation.side], &e.attackAnimation.Clips[e.attackAnimation.clipLoaded], screen, &e.pos);
}
void attackPerso(Ennemi *e, SDL_Surface *screen)
{
    e->attackAnimation.clipLoaded++;
    if (e->attackAnimation.clipLoaded >= e->attackAnimation.frames)
    {
        printf("Life -1\n");
        e->attackAnimation.clipLoaded = 0;
    }
}