

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "gamehead.h"

SDL_Surface *screen;
SDL_Surface *background;
SDL_Surface *credits;
SDL_Surface *gamebackground;
SDL_Surface *pausemenu;
SDL_Surface *settings;
SDL_Surface *resumebtn_u;
SDL_Surface *resumebtn_s;
SDL_Surface *donebtn_u;
SDL_Surface *donebtn_s;
SDL_Surface *quitbtn_u;
SDL_Surface *quitbtn_s;
SDL_Surface *creditsbtn_u;
SDL_Surface *creditsbtn_s;
SDL_Surface *continuebtn_u;
SDL_Surface *continuebtn_s;
SDL_Surface *gitbtn_u;
SDL_Surface *gitbtn_s;
SDL_Surface *settingsbtnreal_u;
SDL_Surface *settingsbtnreal_s;
SDL_Surface *settingsbtn_u;
SDL_Surface *settingsbtn_s;
SDL_Surface *gamenameA;
SDL_Surface *gamenameB;
SDL_Surface *leftarrow;
SDL_Surface *rightarrow;
Mix_Music *music;
Mix_Chunk *scratch;
TTF_Font *fontSmall;
TTF_Font *font;
TTF_Font *fontBig;

SDL_Rect posquitbtn;
SDL_Rect poscreditsbtn;
SDL_Rect posquitbtn;
SDL_Rect poscontinuebtn;
SDL_Rect posgitbtn;
SDL_Rect possettingsbtn;
SDL_Event event;
int doneselectedsettings, volume, ccl, x, y, continueselected, creditsselected, quitselected, gitselected, settingsselected, selectedsettingsreal, selectedresume;
SDL_Color white;
SDL_Color black;

int init()
{

    // Initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return 0;
    }

    // Set up the screen
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);

    // If there was an error in setting up the screen
    if (screen == NULL)
    {
        return 0;
    }
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        return 0;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 64) == -1)
    {
        return 0;
    }
    // Set the window caption
    SDL_WM_SetCaption("AR:T", NULL);

    // If everything initialized fine
    return 1;
}

int load_files()
{
    background = load_image("images/background.png");
    gamebackground = load_image("images/gamebackground.png");
    pausemenu = IMG_Load("images/pausemenu.png");
    credits = IMG_Load("images/credits.png");
    settings = IMG_Load("images/settings.png");
    donebtn_u = IMG_Load("images/done_u.png");
    donebtn_s = IMG_Load("images/done_s.png");
    quitbtn_u = IMG_Load("images/exitbtn_u.png");
    creditsbtn_u = IMG_Load("images/creditsbtn_u.png");
    continuebtn_u = IMG_Load("images/continuebtn_u.png");
    gitbtn_u = IMG_Load("images/gitbtn_u.png");
    resumebtn_u = IMG_Load("images/resumebtn_u.png");
    settingsbtn_u = IMG_Load("images/settingsbtn_u.png");
    settingsbtnreal_u = IMG_Load("images/settingsbtnreal_u.png");
    quitbtn_s = IMG_Load("images/exitbtn_s.png");
    creditsbtn_s = IMG_Load("images/creditsbtn_s.png");
    continuebtn_s = IMG_Load("images/continuebtn_s.png");
    gitbtn_s = IMG_Load("images/gitbtn_s.png");
    resumebtn_s = IMG_Load("images/resumebtn_s.png");
    settingsbtn_s = IMG_Load("images/settingsbtn_s.png");
    settingsbtnreal_s = IMG_Load("images/settingsbtnreal_s.png");
    music = Mix_LoadMUS("sounds/beat.mp3");
    fontSmall = TTF_OpenFont("fonts/Retro.ttf", 24);
    font = TTF_OpenFont("fonts/Retro.ttf", 48);
    fontBig = TTF_OpenFont("fonts/Retro.ttf", 72);

    if (background == NULL || quitbtn_u == NULL || creditsbtn_u == NULL || continuebtn_u == NULL || gitbtn_u == NULL || settingsbtn_u == NULL || quitbtn_s == NULL || creditsbtn_s == NULL || continuebtn_s == NULL || gitbtn_s == NULL || settingsbtn_s == NULL || donebtn_s == NULL || donebtn_u == NULL || gamebackground == NULL || pausemenu == NULL || settingsbtnreal_s == NULL || settingsbtnreal_u == NULL || resumebtn_s == NULL || resumebtn_u == NULL)
    {
        return 0;
    }

    // If there was a problem loading the music
    if (music == NULL)
    {

        return 0;
    }

    if (font == NULL)
    {
        return 0;
    }

    // Load the sound effects
    scratch = Mix_LoadWAV("sounds/scratch.wav");

    // If there was a problem loading the sound effects
    if ((scratch == NULL))
    {
        return 0;
    }
    // If everything loaded fine
    return 1;
}

int menu(clock_t *last, int *actpos, int *actpos_previous)
{
    clock_t current = clock();
    if (current >= (*last + TIME_TO_WAIT * CLOCKS_PER_SEC))
    {
        if (ccl == 0)
        {
            afficher_ecran(896.01, 305.14, gamenameA, screen);
            ccl = 1;
        }
        else
        {
            afficher_ecran(896.01, 305.14, gamenameB, screen);
            ccl = 0;
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

                if (continueselected == 0)
                {
                    continueselected = 1;
                    afficher_ecran(766, 534, continuebtn_s, screen);
                    afficher_ecran(684, 534, leftarrow, screen);
                    afficher_ecran(1175, 534, rightarrow, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (continueselected == 1)
                {
                    continueselected = 0;
                    show_menu();
                    SDL_Flip(screen);
                }
            }
            if (x >= 1791 && x <= 1891 && y >= 20 && y <= 126)
            {
                if (settingsselected == 0)
                {
                    settingsselected = 1;
                    afficher_ecran(1792, 24, settingsbtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (settingsselected == 1)
                {
                    settingsselected = 0;
                    afficher_ecran(1792, 24, settingsbtn_u, screen);
                    SDL_Flip(screen);
                }
            }
            if (x >= 770 && x <= 1149 && y >= 680 && y <= 790)
            {
                if (creditsselected == 0)
                {
                    creditsselected = 1;
                    afficher_ecran(760, 680, creditsbtn_s, screen);
                    afficher_ecran(684, 680, leftarrow, screen);
                    afficher_ecran(1175, 680, rightarrow, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (creditsselected == 1)
                {
                    creditsselected = 0;
                    show_menu();
                    SDL_Flip(screen);
                }
            }
            if (x >= 770 && x <= 1149 && y >= 810 && y <= 930)
            {
                if (quitselected == 0)
                {
                    quitselected = 1;
                    afficher_ecran(766, 814, quitbtn_s, screen);
                    afficher_ecran(684, 814, leftarrow, screen);
                    afficher_ecran(1175, 814, rightarrow, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (quitselected == 1)
                {
                    quitselected = 0;
                    show_menu();
                    SDL_Flip(screen);
                }
            }
            if (x >= 1636 && x <= 1745 && y >= 20 && y <= 126)
            {
                if (gitselected == 0)
                {
                    gitselected = 1;
                    afficher_ecran(1636, 20, gitbtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (gitselected == 1)
                {
                    gitselected = 0;
                    afficher_ecran(1636, 20, gitbtn_u, screen);
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
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                // actpos = 2;
            }
            if (x >= 770 && x <= 1149 && y >= 540 && y <= 650) // Continue
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos_previous = 1;
                *actpos = 2;
                show_game();
                SDL_Flip(screen);
            }
            if (x >= 770 && x <= 1149 && y >= 680 && y <= 790) // Credits
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 1;
                }
                *actpos = 3;
                show_credits();
                SDL_Flip(screen);
            }
            if (x >= 1791 && x <= 1891 && y >= 20 && y <= 126) // Settings
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos_previous = 1;
                *actpos = 4;
                show_settings();
                SDL_Flip(screen);
            }
            if (x >= 770 && x <= 1149 && y >= 810 && y <= 930) // Quit
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
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
                    if (Mix_PlayMusic(music, -1) == -1)
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

int credit(int *actpos)
{
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
                    if (Mix_PlayMusic(music, -1) == -1)
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

                if (doneselectedsettings == 0)
                {
                    doneselectedsettings = 1;
                    afficher_ecran(776, 779, donebtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (doneselectedsettings == 1)
                {
                    doneselectedsettings = 0;
                    show_credits();
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
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                show_menu();
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

int setting(int *actpos, int actpos_previous)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 775 && x <= 1166 && y >= 779 && y <= 890)
            {

                if (doneselectedsettings == 0)
                {
                    doneselectedsettings = 1;
                    afficher_ecran(776, 779, donebtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (doneselectedsettings == 1)
                {
                    doneselectedsettings = 0;
                    show_settings();
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
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                if (actpos_previous == 1)
                    show_menu();
                if (actpos_previous == 5)
                    show_pausemenu();
                *actpos = actpos_previous;
                // applysettings
            }
            if (x >= 1108 && x <= 1121 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                volume = 19;
                show_settings();
                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1128 && x <= 1141 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                volume = 35;
                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                show_settings();
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1148 && x <= 1161 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                volume = 51;

                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                show_settings();
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1168 && x <= 1181 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                volume = 67;
                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                show_settings();
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1188 && x <= 1201 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                volume = 83;
                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                show_settings();
                SDL_Flip(screen);
                // applysettings
            }
            if (x >= 1208 && x <= 1221 && y >= 386 && y <= 477)
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                volume = 128;
                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                show_settings();
                SDL_Flip(screen);
                // applysettings
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_j)
            {
                if (actpos_previous == 1)
                    show_menu();
                if (actpos_previous == 2)
                {
                    // load game progress
                    show_game();
                }
                *actpos = actpos_previous;
            }
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(music, -1) == -1)
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

int game(int *actpos)
{
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
                    if (Mix_PlayMusic(music, -1) == -1)
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
                show_pausemenu();
                SDL_Flip(screen);
                *actpos = 5;
            }
        }
        if (event.type == SDL_QUIT)
            return 1;
    }
    return 0;
}

int pause(int *actpos, int *actpos_previous)
{

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
                    if (Mix_PlayMusic(music, -1) == -1)
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
                show_game();
                SDL_Flip(screen);
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            x = event.button.x;
            y = event.button.y;
            if (x >= 760 && x <= 1159 && y >= 665 && y <= 784) // quit
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                return 1;
            }
            if (x >= 760 && x <= 1159 && y >= 413 && y <= 532) // resume
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                // load the game with the save
                show_game();
                SDL_Flip(screen);
                *actpos = 2;
            }
            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659) // settings
            {
                if (Mix_PlayChannel(-1, scratch, 0) == -1)
                {
                    return 2;
                }
                *actpos_previous = 5;
                *actpos = 4;
                show_settings();
                SDL_Flip(screen);
            }
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 760 && x <= 1159 && y >= 665 && y <= 784)
            {

                if (quitselected == 0)
                {
                    quitselected = 1;
                    afficher_ecran(760, 665, quitbtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (quitselected == 1)
                {
                    quitselected = 0;
                    show_pausemenu();
                    SDL_Flip(screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 413 && y <= 532)
            {

                if (selectedresume == 0)
                {
                    selectedresume = 1;
                    afficher_ecran(760, 413, resumebtn_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (selectedresume == 1)
                {
                    selectedresume = 0;
                    show_pausemenu();
                    SDL_Flip(screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659)
            {

                if (selectedsettingsreal == 0)
                {
                    selectedsettingsreal = 1;
                    afficher_ecran(760, 540, settingsbtnreal_s, screen);
                    SDL_Flip(screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659)
            {

                if (selectedsettingsreal == 0)
                {
                    selectedsettingsreal = 1;
                    afficher_ecran(760, 540, settingsbtnreal_s, screen);
                    SDL_Flip(screen);
                }
            }
            else
            {
                if (selectedsettingsreal == 1)
                {
                    selectedsettingsreal = 0;
                    show_pausemenu();
                    SDL_Flip(screen);
                }
            }
        }
    }
    if (event.type == SDL_QUIT)
        return 1;
    return 0;
}

int afficher_menu()
{
    show_menu();
    gamenameA = TTF_RenderText_Solid(font, "AR:T", white);
    gamenameB = TTF_RenderText_Solid(font, "AR:T", black);
    leftarrow = TTF_RenderText_Solid(fontBig, ">", white);
    rightarrow = TTF_RenderText_Solid(fontBig, "<", white);

    int quit = 0;
    // Where we currently are
    // For instance, 1 stands for menu, 2 Stands for ingame, 3 Stands for Credits, 4 stands for Settings
    int actpos_previous = 1, actpos = 1;
    // If there was an error in rendering
    if (gamenameA == NULL || gamenameB == NULL)
    {
        return 1;
    }
    if (SDL_Flip(screen) == -1)
    {
        return 1;
    }

    if (Mix_PlayMusic(music, -1) == -1)
    {
        return 1;
    }
    clock_t last = clock();
    while (quit == 0)
    {

        if (actpos == 1) // If we are in the main menu
        {
            quit = menu(&last, &actpos, &actpos_previous);
            if (quit == 2)
                return 1;
        }
        if (actpos == 3)
        {
            quit = credit(&actpos);
            if (quit == 2)
                return 1;
        }
        if (actpos == 4)
        {
            quit = setting(&actpos, actpos_previous);
            if (quit == 2)
                return 1;
        }
        if (actpos == 2)
        { // State of Game
            quit = game(&actpos);
            if (quit == 2)
                return 1;
        }
        if (actpos == 5)
        {
            quit = pause(&actpos, &actpos_previous);
            if (quit == 2)
                return 1;
        }
    }
    return 0;
}

void show_menu()
{
    afficher_ecran(0, 0, background, screen);
    afficher_ecran(896.01, 305.14, gamenameA, screen);
    afficher_ecran(766, 814, quitbtn_u, screen);
    afficher_ecran(760, 680, creditsbtn_u, screen);
    afficher_ecran(766, 534, continuebtn_u, screen);
    afficher_ecran(1792, 24, settingsbtn_u, screen);
    afficher_ecran(1636, 20, gitbtn_u, screen);
}

void show_pausemenu()
{
    afficher_ecran(0, 0, gamebackground, screen);
    afficher_ecran(0, 0, pausemenu, screen);
    afficher_ecran(760, 413, resumebtn_u, screen);
    afficher_ecran(760, 540, settingsbtnreal_u, screen);
    afficher_ecran(760, 665, quitbtn_u, screen);
}

void show_game()
{
    afficher_ecran(0, 0, gamebackground, screen);
}

void show_credits()
{
    afficher_ecran(584, 164, credits, screen);
    afficher_ecran(776, 779, donebtn_u, screen);
}
void show_settings()
{
    afficher_ecran(584, 164, settings, screen);
    afficher_ecran(776, 779, donebtn_u, screen);
    FillRect(1207, 370, 14, 87, 0x979797, screen);
    FillRect(1187, 370, 14, 87, 0x979797, screen);
    FillRect(1167, 370, 14, 87, 0x979797, screen);
    FillRect(1147, 370, 14, 87, 0x979797, screen);
    FillRect(1127, 370, 14, 87, 0x979797, screen);
    FillRect(1107, 370, 14, 87, 0x979797, screen);
    switch (volume)
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

void finprog()
{

    Mix_FreeChunk(scratch);
    SDL_FreeSurface(background);
    SDL_FreeSurface(gamebackground);
    SDL_FreeSurface(settingsbtnreal_s);
    SDL_FreeSurface(settingsbtnreal_u);
    SDL_FreeSurface(settings);
    SDL_FreeSurface(credits);
    SDL_FreeSurface(quitbtn_u);
    SDL_FreeSurface(creditsbtn_u);
    SDL_FreeSurface(continuebtn_u);
    SDL_FreeSurface(settingsbtn_u);
    SDL_FreeSurface(gitbtn_u);
    SDL_FreeSurface(donebtn_u);
    SDL_FreeSurface(quitbtn_s);
    SDL_FreeSurface(creditsbtn_s);
    SDL_FreeSurface(continuebtn_s);
    SDL_FreeSurface(settingsbtn_s);
    SDL_FreeSurface(gitbtn_s);
    SDL_FreeSurface(donebtn_s);
    SDL_FreeSurface(gamenameA);
    SDL_FreeSurface(gamenameB);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(pausemenu);
    // Quit SDL
    SDL_Quit();
}