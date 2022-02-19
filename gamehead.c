#include "gamehead.h"

int afficher_menu(btn *B,menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, SDL_Surface *screen)
{
    show_menu(B,MI, SI, screen);

    int frame = 0;
    int cap = 1;
    Timer fps;
    int quit = 0;
    int actpos_previous = 1, actpos = 1;
    
    if (Mix_PlayMusic(M->music, -1) == -1)
    {
        return 1;
    }

    while (quit == 0)
    {
        start(&fps);
        if (actpos == 1) // If we are in the main menu
        {
            show_menu(B,MI,SI,screen);
            if (frame >= 8){
                frame = 0;
            }
            afficher_ecran(0,0,MI->rainspr,screen, &MI->rainclip[frame]);

            quit = menu(B,GI, M, MI, SI, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 3)
        {
            quit = credit(B, M, MI, SI, &actpos, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 4)
        {
            quit = setting(B, PI, MI, GI, SI, M, &actpos, actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 2)
        { // State of Game
            quit = game(B,MI, GI, PI, M, &actpos, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 5)
        {
            quit = pause(B,SI, GI, PI, MI, M, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
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


void finprog(btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, SDL_Surface *screen)
{

    Mix_FreeChunk(M->scratch);
    SDL_FreeSurface(MI->background);
    SDL_FreeSurface(GI->gamebackground);
    SDL_FreeSurface(B->settingsbtnreal[1]);
    SDL_FreeSurface(B->settingsbtnreal[0]);
    SDL_FreeSurface(SI->settings);
    SDL_FreeSurface(MI->credits);
    SDL_FreeSurface(B->quitbtn[0]);
    SDL_FreeSurface(B->creditsbtn[0]);
    SDL_FreeSurface(B->continuebtn[0]);
    SDL_FreeSurface(B->settingsbtn[0]);
    SDL_FreeSurface(B->gitbtn[0]);
    SDL_FreeSurface(B->donebtn[0]);
    SDL_FreeSurface(B->quitbtn[1]);
    SDL_FreeSurface(B->creditsbtn[1]);
    SDL_FreeSurface(B->continuebtn[1]);
    SDL_FreeSurface(B->settingsbtn[1]);
    SDL_FreeSurface(B->gitbtn[1]);
    SDL_FreeSurface(B->donebtn[1]);
    SDL_FreeSurface(B->fsbtn[0]);
    SDL_FreeSurface(B->fsbtn[1]);
    SDL_FreeSurface(B->fsbtn[2]);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(PI->pausemenu);
    SDL_FreeSurface(MI->btnreset);
    SDL_FreeSurface (MI->rainspr);
    SDL_FreeSurface(MI->gamename);
    SDL_FreeSurface(MI->rightarrow);
    SDL_FreeSurface(MI->leftarrow);
    // Quit SDL
    SDL_Quit();
}
