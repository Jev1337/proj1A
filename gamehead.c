#include "gamehead.h"

int afficher_menu(btndim *BD, btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, Ennemi *en, background *b, SDL_Surface *screen)
{
    show_menu(BD, B, MI, SI, screen);
    enigme e;
    int frame = 0;
    int cap = 1;
    Timer fps;
    int quit = 0;
    int actpos_previous = 1, actpos = 1;
    PickUp coin;
    initEnnemi(en);
    initCoin(&coin);
    init_bg(b);
    if (Mix_PlayMusic(M->music, -1) == -1)
    {
        return 1;
    }

    while (quit == 0)
    {
        start(&fps);
        if (actpos == 1) // If we are in the main menu
        {
            show_menu(BD, B, MI, SI, screen);
            if (frame >= 8)
            {
                frame = 0;
            }
            
            afficher_ecran(0, 0, MI->rainspr, screen, &MI->rainclip[frame]);

            quit = menu(BD, B, GI, M, MI, SI, p, b, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 3)
        {
            quit = credit(BD, B, M, MI, SI, &actpos, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 4)
        {
            quit = setting(BD, B, PI, MI, GI, SI, M,b, &actpos, actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 2)
        { // State of Game

            quit = game(BD, B, MI, GI, PI, M, p, en, &coin,b, &actpos, screen);
            if (quit == 2)
                return 1;
            if (actpos == 1)
            {
                cleancharacter(p);
                freeEnnemie(*en);
            }
        }
        if (actpos == 5)
        {
            quit = pause(BD, B, SI, GI, PI, MI, M,b, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 6)
        {
            quit = init_enigme(&e, "enigme.txt", screen);
            if (quit == 2)
                return 1;
            actpos = 2;
        }
        if (SDL_Flip(screen) == -1)
        {
            return 1;
        }

        // Increment the frame counter
        frame++;
        if ((cap == 1) && (get_ticks(&fps) < 1000 / FRAMES_PER_SECOND))
        {
            // Sleep the remaining frame time
            SDL_Delay((1000 / FRAMES_PER_SECOND) - get_ticks(&fps));
        }
    }
    return 0;
}

void finprog(btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, SDL_Surface *screen)
{

    Mix_FreeChunk(M->scratch);
    SDL_FreeSurface(MI->background);
    SDL_FreeSurface(GI->gamebackground);
    SDL_FreeSurface(SI->settings);
    SDL_FreeSurface(MI->credits);
    SDL_FreeSurface(B->menubtns_u[0]);
    SDL_FreeSurface(B->menubtns_u[1]);
    SDL_FreeSurface(B->menubtns_u[2]);
    SDL_FreeSurface(B->menubtns_u[3]);
    SDL_FreeSurface(B->menubtns_u[4]);
    SDL_FreeSurface(B->donebtn[0]);
    SDL_FreeSurface(B->menubtns_s[0]);
    SDL_FreeSurface(B->menubtns_s[1]);
    SDL_FreeSurface(B->menubtns_s[2]);
    SDL_FreeSurface(B->menubtns_s[3]);
    SDL_FreeSurface(B->menubtns_s[4]);
    SDL_FreeSurface(B->donebtn[1]);
    SDL_FreeSurface(B->fsbtn[0]);
    SDL_FreeSurface(B->fsbtn[1]);
    SDL_FreeSurface(B->fsbtn[2]);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(PI->pausemenu);
    SDL_FreeSurface(MI->btnreset);
    SDL_FreeSurface(MI->rainspr);
    SDL_FreeSurface(MI->gamename);
    SDL_FreeSurface(MI->rightarrow);
    SDL_FreeSurface(MI->leftarrow);
    // Quit SDL
    SDL_Quit();
}
