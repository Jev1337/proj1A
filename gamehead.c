

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "gamehead.h"


SDL_Surface *init()
{
    SDL_Surface *screen;
    // Initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return NULL;
    }

    // Set up the screen
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);

    // If there was an error in setting up the screen
    if (screen == NULL)
    {
        return NULL;
    }
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        return NULL;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 64) == -1)
    {
        return NULL;
    }
    // Set the window caption
    SDL_WM_SetCaption("AR:T", NULL);

    // If everything initialized fine
    return screen;
}

int load_files(menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M)
{
    M->volume = 128;
    MI->creditsselected = 0;
    MI->continueselected = 0;
    MI->gitselected = 0;
    MI->quitselected = 0;
    MI->settingsselected = 0;
    MI->background = load_image("images/background.png");
    GI->gamebackground = load_image("images/gamebackground.png");
    PI->pausemenu = IMG_Load("images/pausemenu.png");
    MI->credits = IMG_Load("images/credits.png");
    SI->settings = IMG_Load("images/settings.png");
    SI->donebtn_u = IMG_Load("images/done_u.png");
    SI->donebtn_s = IMG_Load("images/done_s.png");
    MI->quitbtn_u = IMG_Load("images/exitbtn_u.png");
    MI->creditsbtn_u = IMG_Load("images/creditsbtn_u.png");
    MI->continuebtn_u = IMG_Load("images/continuebtn_u.png");
    MI->gitbtn_u = IMG_Load("images/gitbtn_u.png");
    PI->resumebtn_u = IMG_Load("images/resumebtn_u.png");
    MI->settingsbtn_u = IMG_Load("images/settingsbtn_u.png");
    PI->settingsbtnreal_u = IMG_Load("images/settingsbtnreal_u.png");
    MI->quitbtn_s = IMG_Load("images/exitbtn_s.png");
    MI->creditsbtn_s = IMG_Load("images/creditsbtn_s.png");
    MI->continuebtn_s = IMG_Load("images/continuebtn_s.png");
    MI->gitbtn_s = IMG_Load("images/gitbtn_s.png");
    PI->resumebtn_s = IMG_Load("images/resumebtn_s.png");
    MI->settingsbtn_s = IMG_Load("images/settingsbtn_s.png");
    PI->settingsbtnreal_s = IMG_Load("images/settingsbtnreal_s.png");
    M->music = Mix_LoadMUS("sounds/beat.mp3");
    M->font = TTF_OpenFont("fonts/Retro.ttf", 48);
    M->fontBig = TTF_OpenFont("fonts/Retro.ttf", 72);
    if ( SI->settings == NULL || MI->background == NULL || MI->quitbtn_u == NULL || MI->creditsbtn_u == NULL || MI->continuebtn_u == NULL || MI->gitbtn_u == NULL || MI->settingsbtn_u == NULL || MI->quitbtn_s == NULL || MI->creditsbtn_s == NULL || MI->continuebtn_s == NULL || MI->gitbtn_s == NULL || MI->settingsbtn_s == NULL || SI->donebtn_s == NULL || SI->donebtn_u == NULL || GI->gamebackground == NULL || PI->pausemenu == NULL || PI->settingsbtnreal_s == NULL || PI->settingsbtnreal_u == NULL || PI->resumebtn_s == NULL || PI->resumebtn_u == NULL)
    {
        return 0;
    }

    // If there was a problem loading the music
    if (M->music == NULL)
    {

        return 0;
    }

    if (M->font == NULL)
    {
        return 0;
    }

    // Load the sound effects
    M->scratch = Mix_LoadWAV("sounds/scratch.wav");

    // If there was a problem loading the sound effects
    if ((M->scratch == NULL))
    {
        return 0;
    }
    // If everything loaded fine
    return 1;
}

int menu(gameitems *GI, misc *M, menuitems *MI, settingsitems *SI, int *ccl, clock_t *last, int *actpos, int *actpos_previous, SDL_Surface *screen)
{
    SDL_Event event;
    int x,y;
    clock_t current = clock();
    if (current >= (*last + TIME_TO_WAIT * CLOCKS_PER_SEC))
    {
        if (*ccl == 0)
        {
            afficher_ecran(896.01, 305.14, MI->gamenameA, screen);
            *ccl = 1;
        }
        else
        {
            afficher_ecran(896.01, 305.14, MI->gamenameB, screen);
            *ccl = 0;
        }
        *last = current;
        SDL_Flip(screen);
    }

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 770 && x <= 1149 && y >= 540 && y <= 650)
            {

                if (MI->continueselected == 0)
                {
                    MI->continueselected = 1;
                    afficher_ecran(766, 534, MI->continuebtn_s, screen);
                    afficher_ecran(684, 534, MI->leftarrow, screen);
                    afficher_ecran(1175, 534, MI->rightarrow, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (MI->continueselected == 1)
                {
                    MI->continueselected = 0;
                    show_menu(MI, screen);
                    SDL_Flip(screen);
                }
            }
            if (x >= 1791 && x <= 1891 && y >= 20 && y <= 126)
            {
                if (MI->settingsselected == 0)
                {
                    MI->settingsselected = 1;
                    afficher_ecran(1792, 24, MI->settingsbtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (MI->settingsselected == 1)
                {
                    MI->settingsselected = 0;
                    afficher_ecran(1792, 24, MI->settingsbtn_u, screen);
                    SDL_Flip(screen);
                }
            }
            if (x >= 770 && x <= 1149 && y >= 680 && y <= 790)
            {
                if (MI->creditsselected == 0)
                {
                    MI->creditsselected = 1;
                    afficher_ecran(760, 680, MI->creditsbtn_s, screen);
                    afficher_ecran(684, 680, MI->leftarrow, screen);
                    afficher_ecran(1175, 680, MI->rightarrow, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (MI->creditsselected == 1)
                {
                    MI->creditsselected = 0;
                    show_menu(MI, screen);
                    SDL_Flip(screen);
                }
            }
            if (x >= 770 && x <= 1149 && y >= 810 && y <= 930)
            {
                if (MI->quitselected == 0)
                {
                    MI->quitselected = 1;
                    afficher_ecran(766, 814, MI->quitbtn_s, screen);
                    afficher_ecran(684, 814, MI->leftarrow, screen);
                    afficher_ecran(1175, 814, MI->rightarrow, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (MI->quitselected == 1)
                {
                    MI->quitselected = 0;
                    show_menu(MI,screen);
                    SDL_Flip(screen);
                }
            }
            if (x >= 1636 && x <= 1745 && y >= 20 && y <= 126)
            {
                if (MI->gitselected == 0)
                {
                    MI->gitselected = 1;
                    afficher_ecran(1636, 20, MI->gitbtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (MI->gitselected == 1)
                {
                    MI->gitselected = 0;
                    afficher_ecran(1636, 20, MI->gitbtn_u, screen);
                    SDL_Flip(screen);
                }
            }
        }

        if (event.type == SDL_QUIT)
            return 1;
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            x = event.button.x;
            y = event.button.y;
            if (x >= 1636 && x <= 1745 && y >= 20 && y <= 126) // Gitbutton
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                // actpos = 2;
            }
            if (x >= 770 && x <= 1149 && y >= 540 && y <= 650) // Continue
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos_previous = 1;
                *actpos = 2;
                show_game(GI,screen);
                SDL_Flip(screen);
            }
            if (x >= 770 && x <= 1149 && y >= 680 && y <= 790) // Credits
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos = 3;
                show_credits(MI,SI,screen);
                SDL_Flip(screen);
            }
            if (x >= 1791 && x <= 1891 && y >= 20 && y <= 126) // Settings
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos_previous = 1;
                *actpos = 4;
                show_settings(SI,M, screen);
                SDL_Flip(screen);
            }
            if (x >= 770 && x <= 1149 && y >= 810 && y <= 930) // Quit
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                return 1;
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 2;
                    }
                }
                // If music is being played
                else
                {
                    // If the music is paused
                    if (Mix_PausedMusic() == 1)
                    {
                        // Resume the music
                        Mix_ResumeMusic();
                    }
                    // If the music is playing
                    else
                    {
                        // Pause the music
                        Mix_PauseMusic();
                    }
                }
            }
            else if (event.key.keysym.sym == SDLK_x)
            {
                // Stop the music
                Mix_HaltMusic();
            }
        }
    }
    return 0;
}

int credit(misc *M, menuitems *MI, settingsitems *SI, int *actpos, SDL_Surface *screen)
{
    SDL_Event event;
    int x,y;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 1;
                    }
                }
                // If music is being played
                else
                {
                    // If the music is paused
                    if (Mix_PausedMusic() == 1)
                    {
                        // Resume the music
                        Mix_ResumeMusic();
                    }
                    // If the music is playing
                    else
                    {
                        // Pause the music
                        Mix_PauseMusic();
                    }
                }
            }
            else if (event.key.keysym.sym == SDLK_x)
            {
                // Stop the music
                Mix_HaltMusic();
            }
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 775 && x <= 1166 && y >= 779 && y <= 890)
            {

                if (SI->doneselectedsettings == 0)
                {
                    SI->doneselectedsettings = 1;
                    afficher_ecran(776, 779, SI->donebtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (SI->doneselectedsettings == 1)
                {
                    SI->doneselectedsettings = 0;
                    show_credits(MI, SI, screen);
                    SDL_Flip(screen);
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            x = event.button.x;
            y = event.button.y;
            if (x >= 775 && x <= 1166 && y >= 779 && y <= 890)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                show_menu(MI, screen);
                SDL_Flip(screen);
                *actpos = 1;
                // applysettings
            }
        }
        if (event.type == SDL_QUIT)
            return 1;
    }
    return 0;
}

int setting(pauseitems *PI, menuitems *MI, gameitems *GI, settingsitems *SI,misc *M, int *actpos, int actpos_previous, SDL_Surface *screen)
{
    SDL_Event event;
    int x,y;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 775 && x <= 1166 && y >= 779 && y <= 890)
            {

                if (SI->doneselectedsettings == 0)
                {
                    SI->doneselectedsettings = 1;
                    afficher_ecran(776, 779, SI->donebtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (SI->doneselectedsettings == 1)
                {
                    SI->doneselectedsettings = 0;
                    show_settings(SI, M,screen);
                    SDL_Flip(screen);
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            x = event.button.x;
            y = event.button.y;
            if (x >= 775 && x <= 1166 && y >= 779 && y <= 890)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                if (actpos_previous == 1)
                    show_menu(MI, screen);
                if (actpos_previous == 5)
                    show_pausemenu(MI,GI,PI,screen);
                *actpos = actpos_previous;
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1108 && x <= 1121 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                M->volume = 19;
                show_settings(SI, M, screen);
                Mix_VolumeMusic(M->volume);
                Mix_Volume(-1, M->volume);
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1128 && x <= 1141 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                M->volume = 35;
                Mix_VolumeMusic(M->volume);
                Mix_Volume(-1, M->volume);
                show_settings(SI, M, screen);
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1148 && x <= 1161 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                M->volume = 51;

                Mix_VolumeMusic(M->volume);
                Mix_Volume(-1, M->volume);
                show_settings(SI, M, screen);
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1168 && x <= 1181 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                M->volume = 67;
                Mix_VolumeMusic(M->volume);
                Mix_Volume(-1, M->volume);
                show_settings(SI, M, screen);
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1188 && x <= 1201 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                M->volume = 83;
                Mix_VolumeMusic(M->volume);
                Mix_Volume(-1, M->volume);
                show_settings(SI, M, screen);
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1208 && x <= 1221 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                M->volume = 128;
                Mix_VolumeMusic(M->volume);
                Mix_Volume(-1, M->volume);
                show_settings(SI, M, screen);
                SDL_Flip(screen);
                // applysettings
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_j)
            {
                if (actpos_previous == 1)
                    show_menu(MI,screen);
                if (actpos_previous == 2)
                {
                    // load game progress
                    show_game(GI, screen);
                }
                *actpos = actpos_previous;
            }
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 2;
                    }
                }
                // If music is being played
                else
                {
                    // If the music is paused
                    if (Mix_PausedMusic() == 1)
                    {
                        // Resume the music
                        Mix_ResumeMusic();
                    }
                    // If the music is playing
                    else
                    {
                        // Pause the music
                        Mix_PauseMusic();
                    }
                }
            }
            else if (event.key.keysym.sym == SDLK_x)
            {
                // Stop the music
                Mix_HaltMusic();
            }
        }
        if (event.type == SDL_QUIT)
            return 1;
    }
    return 0;
}

int game(menuitems *MI,gameitems *GI,pauseitems *PI,misc *M, int *actpos, SDL_Surface *screen)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 2;
                    }
                }
                // If music is being played
                else
                {
                    // If the music is paused
                    if (Mix_PausedMusic() == 1)
                    {
                        // Resume the music
                        Mix_ResumeMusic();
                    }
                    // If the music is playing
                    else
                    {
                        // Pause the music
                        Mix_PauseMusic();
                    }
                }
            }
            if (event.key.keysym.sym == SDLK_x)
            {
                // Stop the music
                Mix_HaltMusic();
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                show_pausemenu(MI,GI,PI,screen);
                SDL_Flip(screen);
                *actpos = 5;
            }
        }
        if (event.type == SDL_QUIT)
            return 1;
    }
    return 0;
}

int pause(settingsitems *SI, gameitems *GI, pauseitems *PI, menuitems *MI, misc *M, int *actpos, int *actpos_previous, SDL_Surface *screen)
{
    SDL_Event event;
    int x,y;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 2;
                    }
                }
                // If music is being played
                else
                {
                    // If the music is paused
                    if (Mix_PausedMusic() == 1)
                    {
                        // Resume the music
                        Mix_ResumeMusic();
                    }
                    // If the music is playing
                    else
                    {
                        // Pause the music
                        Mix_PauseMusic();
                    }
                }
            }

            if (event.key.keysym.sym == SDLK_x)
            {
                // Stop the music
                Mix_HaltMusic();
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                *actpos = 2;
                show_game(GI, screen);
                SDL_Flip(screen);
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            x = event.button.x;
            y = event.button.y;
            if (x >= 760 && x <= 1159 && y >= 665 && y <= 784) // quit
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                return 1;
            }
            if (x >= 760 && x <= 1159 && y >= 413 && y <= 532) // resume
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                // load the game with the save
                show_game(GI, screen);
                SDL_Flip(screen);
                *actpos = 2;
            }
            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659) // settings
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos_previous = 5;
                *actpos = 4;
                show_settings(SI,M,screen);
                SDL_Flip(screen);
            }
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 760 && x <= 1159 && y >= 665 && y <= 784)
            {

                if (MI->quitselected == 0)
                {
                    MI->quitselected = 1;
                    afficher_ecran(760, 665, MI->quitbtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (MI->quitselected == 1)
                {
                    MI->quitselected = 0;
                    show_pausemenu(MI,GI,PI, screen);
                    SDL_Flip(screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 413 && y <= 532)
            {

                if (PI->selectedresume == 0)
                {
                    PI->selectedresume = 1;
                    afficher_ecran(760, 413, PI->resumebtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (PI->selectedresume == 1)
                {
                    PI->selectedresume = 0;
                    show_pausemenu(MI,GI,PI,screen);
                    SDL_Flip(screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659)
            {

                if (PI->selectedsettingsreal == 0)
                {
                    PI->selectedsettingsreal = 1;
                    afficher_ecran(760, 540, PI->settingsbtnreal_s, screen);
                    SDL_Flip(screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659)
            {

                if (PI->selectedsettingsreal == 0)
                {
                    PI->selectedsettingsreal = 1;
                    afficher_ecran(760, 540, PI->settingsbtnreal_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (PI->selectedsettingsreal == 1)
                {
                    PI->selectedsettingsreal = 0;
                    show_pausemenu(MI,GI,PI,screen);
                    SDL_Flip(screen);
                }
            }
        }
    }
    if (event.type == SDL_QUIT)
        return 1;
    return 0;
}

int afficher_menu(menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, SDL_Surface *screen)
{
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {14, 0, 68};
    show_menu(MI,screen);
    MI->gamenameA = TTF_RenderText_Solid(M->font, "AR:T", white);
    MI->gamenameB = TTF_RenderText_Solid(M->font, "AR:T", black);
    MI->leftarrow = TTF_RenderText_Solid(M->fontBig, ">", white);
    MI->rightarrow = TTF_RenderText_Solid(M->fontBig, "<", white);
    int ccl = 0;
    int quit = 0;
    int actpos_previous = 1, actpos = 1;

    if (MI->gamenameA == NULL || MI->gamenameB == NULL)
    {
        return 1;
    }
    if (SDL_Flip(screen) == -1)
    {
        return 1;
    }

    if (Mix_PlayMusic(M->music, -1) == -1)
    {
        return 1;
    }
    clock_t last = clock();
    while (quit == 0)
    {

        if (actpos == 1) // If we are in the main menu
        {
            quit = menu(GI, M, MI,SI, &ccl,&last, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 3)
        {
            quit = credit(M, MI, SI, &actpos, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 4)
        {
            quit = setting(PI, MI, GI, SI, M, &actpos, actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 2)
        { // State of Game
            quit = game(MI, GI, PI , M, &actpos, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 5)
        {
            quit = pause(SI, GI, PI, MI, M,&actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
    }
    return 0;
}

void show_menu(menuitems *MI, SDL_Surface *screen)
{
    afficher_ecran(0, 0, MI->background, screen);
    afficher_ecran(896.01, 305.14, MI->gamenameA, screen);
    afficher_ecran(766, 814, MI->quitbtn_u, screen);
    afficher_ecran(760, 680, MI->creditsbtn_u, screen);
    afficher_ecran(766, 534, MI->continuebtn_u, screen);
    afficher_ecran(1792, 24, MI->settingsbtn_u, screen);
    afficher_ecran(1636, 20, MI->gitbtn_u, screen);
}

void show_pausemenu(menuitems *MI, gameitems *GI, pauseitems *PI, SDL_Surface *screen)
{
    afficher_ecran(0, 0, GI->gamebackground, screen);
    afficher_ecran(0, 0, PI->pausemenu, screen);
    afficher_ecran(760, 413, PI->resumebtn_u, screen);
    afficher_ecran(760, 540, PI->settingsbtnreal_u, screen);
    afficher_ecran(760, 665, MI->quitbtn_u, screen);
}

void show_game(gameitems *GI, SDL_Surface *screen)
{
    afficher_ecran(0, 0, GI->gamebackground, screen);
}

void show_credits(menuitems *MI,settingsitems *SI, SDL_Surface *screen)
{
    afficher_ecran(584, 164, MI->credits, screen);
    afficher_ecran(776, 779, SI->donebtn_u, screen);
}
void show_settings(settingsitems *SI, misc *M,SDL_Surface *screen)
{
    afficher_ecran(584, 164, SI->settings, screen);
    afficher_ecran(776, 779, SI->donebtn_u, screen);
    FillRect(1207, 370, 14, 87, 0x979797, screen);
    FillRect(1187, 370, 14, 87, 0x979797, screen);
    FillRect(1167, 370, 14, 87, 0x979797, screen);
    FillRect(1147, 370, 14, 87, 0x979797, screen);
    FillRect(1127, 370, 14, 87, 0x979797, screen);
    FillRect(1107, 370, 14, 87, 0x979797, screen);
    switch (M->volume)
    {
    case 128:
        FillRect(1207, 370, 14, 87, 0x134908, screen);
    case 83:
        FillRect(1187, 370, 14, 87, 0x134908, screen);
    case 67:
        FillRect(1167, 370, 14, 87, 0x134908, screen);
    case 51:
        FillRect(1147, 370, 14, 87, 0x134908, screen);
    case 35:
        FillRect(1127, 370, 14, 87, 0x134908, screen);
    case 19:
        FillRect(1107, 370, 14, 87, 0x134908, screen);
        break;
    }
}

void finprog(menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, SDL_Surface *screen)
{

    Mix_FreeChunk(M->scratch);
    SDL_FreeSurface(MI->background);
    SDL_FreeSurface(GI->gamebackground);
    SDL_FreeSurface(PI->settingsbtnreal_s);
    SDL_FreeSurface(PI->settingsbtnreal_u);
    SDL_FreeSurface(SI->settings);
    SDL_FreeSurface(MI->credits);
    SDL_FreeSurface(MI->quitbtn_u);
    SDL_FreeSurface(MI->creditsbtn_u);
    SDL_FreeSurface(MI->continuebtn_u);
    SDL_FreeSurface(MI->settingsbtn_u);
    SDL_FreeSurface(MI->gitbtn_u);
    SDL_FreeSurface(SI->donebtn_u);
    SDL_FreeSurface(MI->quitbtn_s);
    SDL_FreeSurface(MI->creditsbtn_s);
    SDL_FreeSurface(MI->continuebtn_s);
    SDL_FreeSurface(MI->settingsbtn_s);
    SDL_FreeSurface(MI->gitbtn_s);
    SDL_FreeSurface(SI->donebtn_s);
    SDL_FreeSurface(MI->gamenameA);
    SDL_FreeSurface(MI->gamenameB);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(PI->pausemenu);
    // Quit SDL
    SDL_Quit();
}