#include "character.h"
void initcharacter(character *p, int x)
{
    if (x)
    {
        p->charsprite[0] = IMG_Load("images/leftsheetC.png");
        p->charsprite[1] = IMG_Load("images/rightsheetC.png");

        p->offset.y = 1080 - p->clips[1].h;
        p->offset.w = 366;
        p->offset.h = p->clips[1].h;
    }
    else
    {
        p->direction = 1;
        p->side = -2;
        p->offset.x = 0;
        p->health = 5;
        p->speed = 30;
        p->charsprite[0] = IMG_Load("images/leftsheetC.png");
        p->charsprite[1] = IMG_Load("images/rightsheetC.png");

        p->offset.y = 1080 - p->clips[p->direction].h;
        p->offset.w = 366;
        p->offset.h = p->clips[p->direction].h;
    }
}

void setcharacter(character *p, character *popt, gameitems *GI, pauseitems *PI, Uint8 *keystate)
{
    if (keystate[SDLK_LSHIFT])
    {
        if (p->speed < 100)
        {
            p->speed += 10;
        }
    }
    if (keystate[SDLK_RSHIFT])
    {
        if (p->speed > 10)
        {
            p->speed -= 10;
        }
    }

    if (keystate[SDLK_LEFTPAREN])
    {
        if (p->speed < 100)
        {
            popt->speed += 10;
        }
    }
    if (keystate[SDLK_RIGHTPAREN])
    {
        if (p->speed > 10)
        {
            popt->speed -= 10;
        }
    }

    if (!PI->mvmt)
    {
        if (keystate[SDLK_LEFT] || keystate[SDLK_RIGHT])
        {
            Mix_PlayChannel(2, PI->run, 0);
            PI->mvmt = 1;
        }
    }
    if (keystate[SDLK_LEFT])
    {
        p->side = 0;
    }
    else if (p->side == 0)
    {
        p->side = -1;
    }
    if (keystate[SDLK_RIGHT])
    {
        p->side = 1;
    }
    else if (p->side == 1)
    {
        p->side = -2;
    }
    if (keystate[SDLK_UP])
        PI->mvmt = 0;
    if (keystate[SDLK_LEFT] == 0 && keystate[SDLK_RIGHT] == 0)
    {
        PI->mvmt = 0;
    }
    if (!PI->mvmt)
        Mix_Pause(2);
    if (GI->SecOpt)
    {

        if (!PI->mvmt2)
        {
            if (keystate[SDLK_a] || keystate[SDLK_d])
            {
                Mix_PlayChannel(2, PI->run, 0);
                PI->mvmt2 = 1;
            }
        }

        if (keystate[SDLK_a])
        {
            popt->side = 0;
        }
        else if (popt->side == 0)
        {
            popt->side = -1;
        }
        if (keystate[SDLK_d])
        {
            popt->side = 1;
        }
        else if (popt->side == 1)
        {
            popt->side = -2;
        }
        if (keystate[SDLK_UP])
            PI->mvmt2 = 0;
        if (keystate[SDLK_LEFT] == 0 && keystate[SDLK_RIGHT] == 0)
        {
            PI->mvmt2 = 0;
        }

        if (!PI->mvmt2)
            Mix_Pause(2);
    }
}

void jump(character *p, character *popt, int x, btndim *BD, btn *B, gameitems *GI, Ennemi *e, PickUp coin, background *b, minimap *m, SDL_Surface *screen)
{
    int i, j;
    Mix_Chunk *jump = Mix_LoadWAV("sounds/jump.wav");
    Mix_PlayChannel(1, jump, 0);
    if (x == 1)
    {
        for (j = 10, i = 0; i <= 12; i++, j += 3, p->offset.y -= j)
        {
            if (p->side == 1 | p->side == -2)
            {
                if (p->offset.x < 1920 / 2 - p->offset.w)
                {
                    p->offset.x += p->speed;
                    b->posmask.x += p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += p->speed / 5.3;
                }
                else if (b->posimage.x > -(b->image->w - 1920))
                {
                    if (!GI->SecOpt)
                        b->posimage.x -= p->speed;
                    else
                        b->posimage.x += p->speed;
                    b->posmask.x += p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += p->speed / 5.3;
                }
            }
            else if (p->side == 0 | p->side == -1)
            {
                if (p->offset.x - 10 > 0)
                {
                    p->offset.x -= p->speed;
                    b->posmask.x -= p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= p->speed / 5.3;
                }
                else if (b->posimage.x < 0)
                {
                    if (!GI->SecOpt)
                        b->posimage.x += p->speed;
                    else
                        b->posimage.x -= p->speed;
                    b->posmask.x -= p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= p->speed / 5.3;
                }
            }

            show_game(BD, B, GI, b, screen);
            afficher_character(p, screen);
            if (GI->lvl != 9)
                afficherminimap(*m, GI->zoomable, screen);
            if (GI->lvl == 9 && GI->eshealth != 0)
            {
                if (e->attack)
                {
                    afficherAttack(*e, screen);
                    attackPerso(e, screen);
                }
                else
                    afficherEnnemi(*e, screen);
                deplacerIA(e, p->offset);
            }
            if (GI->lvl == 9)
            {
                afficher_ecran(1300, 800, coin.animation.spriteSheet[0], screen, &coin.animation.Clips[coin.animation.clipLoaded]);
                animerCoin(&coin);
            }
            SDL_Flip(screen);
            SDL_Delay(18);
        }
        for (j = 10, i = 0; i <= 12; i++, j += 3, p->offset.y += j)
        {
            if (p->side == 1 | p->side == -2)
            {
                if (p->offset.x < 1920 / 2 - p->offset.w)
                {
                    p->offset.x += p->speed;
                    b->posmask.x += p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += p->speed / 5.3;
                }
                else if (b->posimage.x > -(b->image->w - 1920))
                {
                    if (!GI->SecOpt)
                        b->posimage.x -= p->speed;
                    else
                        b->posimage.x += p->speed;
                    b->posmask.x += p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += p->speed / 5.3;
                }
            }
            else if (p->side == 0 | p->side == -1)
            {
                if (p->offset.x - 10 > 0)
                {
                    p->offset.x -= p->speed;
                    b->posmask.x -= p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= p->speed / 5.3;
                }
                else if (b->posimage.x < 0)
                {
                    if (!GI->SecOpt)
                        b->posimage.x += p->speed;
                    else
                        b->posimage.x -= p->speed;
                    b->posmask.x -= p->speed;
                    if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= p->speed / 5.3;
                }
            }
            show_game(BD, B, GI, b, screen);
            afficher_character(p, screen);
            if (GI->lvl != 9)
                afficherminimap(*m, GI->zoomable, screen);
            if (GI->lvl == 9 && GI->eshealth != 0)
            {
                if (e->attack)
                {
                    afficherAttack(*e, screen);
                    attackPerso(e, screen);
                }
                else
                    afficherEnnemi(*e, screen);
                deplacerIA(e, p->offset);
            }
            if (GI->lvl == 9)
            {
                afficher_ecran(1300, 800, coin.animation.spriteSheet[0], screen, &coin.animation.Clips[coin.animation.clipLoaded]);
                animerCoin(&coin);
            }
            SDL_Flip(screen);
            SDL_Delay(18);
        }
    }
    //--------------

    if (x == 2)
    {
        for (j = 10, i = 0; i <= 12; i++, j += 3, popt->offset.y -= j)
        {
            if (popt->side == 1 | popt->side == -2)
            {
                if (popt->offset.x < 1920 - popt->offset.w)
                {
                    popt->offset.x += popt->speed;
                    b->posmask2.x += popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += popt->speed / 5.3;*/
                }
                else if (b->posimage2.x > -(b->image->w - 1920))
                {
                    b->posimage2.x += popt->speed;
                    b->posmask2.x += popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += popt->speed / 5.3;*/
                }
            }
            else if (popt->side == 0 | popt->side == -1)
            {
                if (popt->offset.x - 10 > 1920 / 2)
                {
                    popt->offset.x -= popt->speed;
                    b->posmask2.x -= popt->speed;
                    /* if (m->pospoint.x >= m->posminimap.x) // point follow player
                         m->pospoint.x -= popt->speed / 5.3;*/
                }
                else if (b->posimage2.x < 1920 / 2)
                {
                    b->posimage2.x -= popt->speed;
                    b->posmask2.x -= popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= popt->speed / 5.3;*/
                }
            }

            show_game(BD, B, GI, b, screen);
            afficher_character(popt, screen);
            afficherminimap(*m, GI->zoomable, screen);
            if (GI->lvl == 9)
            {

                afficher_ecran(1300, 800, coin.animation.spriteSheet[0], screen, &coin.animation.Clips[coin.animation.clipLoaded]);
                animerCoin(&coin);
                if (e->attack)
                {
                    afficherAttack(*e, screen);
                    attackPerso(e, screen);
                }
                else
                    afficherEnnemi(*e, screen);
                deplacerIA(e, popt->offset);
            }

            SDL_Flip(screen);
            SDL_Delay(18);
        }
        for (j = 10, i = 0; i <= 12; i++, j += 3, popt->offset.y += j)
        {
            if (popt->side == 1 | popt->side == -2)
            {
                if (popt->offset.x < 1920 - popt->offset.w)
                {
                    popt->offset.x += popt->speed;
                    b->posmask2.x += popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += popt->speed / 5.3;*/
                }
                else if (b->posimage2.x > -(b->image2->w - 1920))
                {
                    b->posimage2.x += popt->speed;
                    b->posmask2.x += popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x += popt->speed / 5.3;*/
                }
            }
            else if (popt->side == 0 | popt->side == -1)
            {
                if (popt->offset.x - 10 > 0)
                {
                    popt->offset.x -= popt->speed;
                    b->posmask2.x -= popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= popt->speed / 5.3;*/
                }
                else if (b->posimage2.x < 0)
                {
                    b->posimage2.x -= popt->speed;
                    b->posmask2.x -= popt->speed;
                    /*if (m->pospoint.x >= m->posminimap.x) // point follow player
                        m->pospoint.x -= popt->speed / 5.3;*/
                }
            }
            show_game(BD, B, GI, b, screen);
            afficher_character(popt, screen);
            afficherminimap(*m, GI->zoomable, screen);
            if (GI->lvl == 9)
            {

                afficher_ecran(1300, 800, coin.animation.spriteSheet[0], screen, &coin.animation.Clips[coin.animation.clipLoaded]);
                animerCoin(&coin);
                if (e->attack)
                {
                    afficherAttack(*e, screen);
                    attackPerso(e, screen);
                }
                else
                    afficherEnnemi(*e, screen);
                deplacerIA(e, p->offset);
            }
            SDL_Flip(screen);
            SDL_Delay(18);
        }
    }
}

void changedirection(character *p, character *popt, minimap *m, background *b, gameitems *GI, int SecOpt)
{
    if (p->side == 0)
    {
        if (collisionPP(b->posmask, b->imageM) == 0)
        {
            if (p->offset.x > 0)
            {

                p->offset.x -= p->speed;
                b->posmask.x -= p->speed;
                if (m->pospoint.x >= m->posminimap.x) // point follow player
                    m->pospoint.x -= p->speed / 5.3;
            }
            else if (b->posimage.x < -p->speed)
            {

                b->posmask.x -= p->speed;
                if (!GI->SecOpt)
                    b->posimage.x += p->speed;
                else
                    b->posimage.x -= p->speed;
                if (m->pospoint.x >= m->posminimap.x) // point follow player
                    m->pospoint.x -= p->speed / 5.3;
            }
        }
        p->direction--;
        if (p->direction == -1)
            p->direction = 3;
    }
    else if (p->side == 1)
    {

        // we need to add the condition where if we are in the last point in the level we have to allow the player to move around to the next half of the screen
        if (collisionPP(b->posmask, b->imageM) == 0)
        {
            if (p->offset.x < 1920 / 2 - p->offset.w)
            {
                p->offset.x += p->speed;
                b->posmask.x += p->speed;
                if (m->pospoint.x >= m->posminimap.x) // point follow player
                    m->pospoint.x += p->speed / 5.3;
            }
            else if (b->posimage.x > -(b->image->w - 1920))
            {
                if (!GI->SecOpt)
                    b->posimage.x -= p->speed;
                else
                    b->posimage.x += p->speed;
                b->posmask.x += p->speed;
                if (m->pospoint.x >= m->posminimap.x) // point follow player
                    m->pospoint.x += p->speed / 5.3;
            }
            else if (GI->lvl == 9)
            {
                p->offset.x += p->speed;
                b->posmask.x += p->speed;
                if (m->pospoint.x >= m->posminimap.x) // point follow player
                    m->pospoint.x += p->speed / 5.3;
            }
        }
        p->direction++;
        if (p->direction == 4)
            p->direction = 1;
    }
    else if (p->side == 3)
    {
    }
    else if (p->side == -1)
        p->direction = 3;
    else
        p->direction = 0;

    //----------------------------------
    if (GI->SecOpt)
    {
        if (popt->side == 0)
        {
            if (collisionPP(b->posmask2, b->imageM2) == 0)
            {
                if (popt->offset.x > 1920 / 2)
                {
                    popt->offset.x -= popt->speed;
                    b->posmask2.x -= popt->speed;
                }
                else if (b->posimage2.x < -popt->speed)
                {
                    b->posmask2.x -= popt->speed;
                    b->posimage.x -= popt->speed;
                }
            }
            popt->direction--;
            if (popt->direction == -1)
                popt->direction = 3;
        }
        else if (popt->side == 1)
        {

            // we need to add the condition where if we are in the last point in the level we have to allow the player to move around to the next half of the screen
            if (collisionPP(b->posmask2, b->imageM2) == 0)
            {
                if (popt->offset.x < 1920 - popt->offset.w)
                {
                    popt->offset.x += popt->speed;
                    b->posmask2.x += popt->speed;
                }
                else if (b->posimage.x > -(b->image->w - 1920))
                {
                    b->posimage2.x += popt->speed;
                    b->posmask2.x += popt->speed;
                }
            }
            popt->direction++;
            if (popt->direction == 4)
                popt->direction = 1;
        }
        else if (popt->side == 3)
        {
        }
        else if (popt->side == -1)
            popt->direction = 3;
        else
            popt->direction = 0;
    }
}

void afficher_character(character *p, SDL_Surface *screen)
{
    if (p->side >= 0)
        afficher_ecran(p->offset.x, p->offset.y, p->charsprite[p->side], screen, &p->clips[p->direction]);
    else if (p->side == -1)
        afficher_ecran(p->offset.x, p->offset.y, p->charsprite[0], screen, &p->clips[p->direction]);
    else
        afficher_ecran(p->offset.x, p->offset.y, p->charsprite[1], screen, &p->clips[p->direction]);
}

void cleancharacter(character *p)
{
    SDL_FreeSurface(p->charsprite[0]);
    SDL_FreeSurface(p->charsprite[1]);
}