
#include "gamehead.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <time.h>

#define TIME_TO_WAIT 0.5 /* wait for one second */

SDL_Surface *screen;
SDL_Surface *background;
SDL_Surface *settings;
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
int volume,ccl, x, y, continueselected, creditsselected, quitselected, gitselected, settingsselected, doneselectedsettings;
SDL_Color white;
SDL_Color black;

int init()
{

    //Initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return 0;
    }

    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if (screen == NULL)
    {
        return 0;
    }
    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        return 0;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return 0;
    }
    //Set the window caption
    SDL_WM_SetCaption("AR:T", NULL);

    //If everything initialized fine
    return 1;
}

int load_files()
{
    background = load_image("images/background.png");
    settings = IMG_Load("images/settings.png");
    donebtn_u = IMG_Load("images/done_u.png");
    donebtn_s = IMG_Load("images/done_s.png");
    quitbtn_u = IMG_Load("images/exitbtn_u.png");
    creditsbtn_u = IMG_Load("images/creditsbtn_u.png");
    continuebtn_u = IMG_Load("images/continuebtn_u.png");
    gitbtn_u = IMG_Load("images/gitbtn_u.png");
    settingsbtn_u = IMG_Load("images/settingsbtn_u.png");
    quitbtn_s = IMG_Load("images/exitbtn_s.png");
    creditsbtn_s = IMG_Load("images/creditsbtn_s.png");
    continuebtn_s = IMG_Load("images/continuebtn_s.png");
    gitbtn_s = IMG_Load("images/gitbtn_s.png");
    settingsbtn_s = IMG_Load("images/settingsbtn_s.png");
    music = Mix_LoadMUS("sounds/beat.mp3");
    fontSmall = TTF_OpenFont("fonts/Retro.ttf", 24);
    font = TTF_OpenFont("fonts/Retro.ttf", 48);
    fontBig = TTF_OpenFont("fonts/Retro.ttf", 72);

    if (background == NULL || quitbtn_u == NULL || creditsbtn_u == NULL || continuebtn_u == NULL || gitbtn_u == NULL || settingsbtn_u == NULL || quitbtn_s == NULL || creditsbtn_s == NULL ||
        continuebtn_s == NULL || gitbtn_s == NULL || settingsbtn_s == NULL || donebtn_s == NULL || donebtn_u == NULL)
    {
        return 0;
    }

    //If there was a problem loading the music
    if (music == NULL)
    {

        return 0;
    }

    if (font == NULL)
    {
        return 0;
    }

    //Load the sound effects
    scratch = Mix_LoadWAV("sounds/scratch.wav");

    //If there was a problem loading the sound effects
    if ((scratch == NULL))
    {
        return 0;
    }
    //If everything loaded fine
    return 1;
}

SDL_Surface *load_image(char filename[])
{

    //Temporary storage for the image that's loaded
    SDL_Surface *loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface *optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load(filename);
    //If nothing went wrong in loading the image
    if (loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);
    }
    //Return the optimized image
    return optimizedImage;
}
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{

    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface(src, NULL, dest, &offset);
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

void FillRect(int x, int y, int w, int h, int color) {
  SDL_Rect rect = {x,y,w,h};
  SDL_FillRect(screen, &rect, color);
}

int afficher_menu()
{
    show_menu();
    gamenameA = TTF_RenderText_Solid(font, "AR:T", white);
    gamenameB = TTF_RenderText_Solid(font, "AR:T", black);
    leftarrow = TTF_RenderText_Solid(fontBig, ">", white);
    rightarrow = TTF_RenderText_Solid(fontBig, "<", white);

    int quit = 0;
    //Where we currently are
    //For instance, 1 stands for menu, 2 Stands for ingame, 3 Stands for Credits, 4 stands for Settings
    int actpos_previous = 1, actpos = 1;
    //If there was an error in rendering
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
        if (actpos == 1) //If we are in the main menu
        {

            clock_t current = clock();
            if (current >= (last + TIME_TO_WAIT * CLOCKS_PER_SEC))
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
                last = current;
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
                    quit = 1;
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    x = event.button.x;
                    y = event.button.y;
                    if (x >= 1636 && x <= 1745 && y >= 20 && y <= 126) //Gitbutton
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        //actpos = 2;
                    }
                    if (x >= 770 && x <= 1149 && y >= 540 && y <= 650) //Continue
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        //actpos = 2;
                    }
                    if (x >= 770 && x <= 1149 && y >= 680 && y <= 790) //Credits
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        //actpos = 3;
                    }
                    if (x >= 1791 && x <= 1891 && y >= 20 && y <= 126) //Settings
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        actpos_previous = 1;
                        actpos = 4;
                        show_settings();
                        SDL_Flip(screen);
                    }
                    if (x >= 770 && x <= 1149 && y >= 810 && y <= 930) //Quit
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        quit = 1;
                    }
                }
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_g)
                    {
                        //If there is no music playing
                        if (Mix_PlayingMusic() == 0)
                        {
                            //Play the music
                            if (Mix_PlayMusic(music, -1) == -1)
                            {
                                return 1;
                            }
                        }
                        //If music is being played
                        else
                        {
                            //If the music is paused
                            if (Mix_PausedMusic() == 1)
                            {
                                //Resume the music
                                Mix_ResumeMusic();
                            }
                            //If the music is playing
                            else
                            {
                                //Pause the music
                                Mix_PauseMusic();
                            }
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_c)
                    {
                        //Stop the music
                        Mix_HaltMusic();
                    }
                }
            }
        }
        if (actpos == 4)
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
                            return 1;
                        }
                        if (actpos_previous == 1)
                            show_menu();
                        actpos = actpos_previous;
                        //applysettings
                    }
                    if (x >= 1108 && x <= 1121 && y >= 386 && y <= 477)
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        volume = 19;
                        show_settings();
                        Mix_VolumeMusic(volume);
                        SDL_Flip(screen);
                        //applysettings
                    }
                    if (x >= 1128 && x <= 1141 && y >= 386 && y <= 477)
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        volume = 35;
                        Mix_VolumeMusic(volume);
                        show_settings();
                        SDL_Flip(screen);
                        //applysettings
                    }
                    if (x >= 1148 && x <= 1161 && y >= 386 && y <= 477)
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        volume = 51;
                        Mix_VolumeMusic(volume);
                        show_settings();
                        SDL_Flip(screen);
                        //applysettings
                    }
                    if (x >= 1168 && x <= 1181 && y >= 386 && y <= 477)
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        volume = 67;
                        Mix_VolumeMusic(volume);
                        show_settings();
                        SDL_Flip(screen);
                        //applysettings
                    }
                    if (x >= 1188 && x <= 1201 && y >= 386 && y <= 477)
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        volume = 83;
                        Mix_VolumeMusic(volume);
                        show_settings();
                        SDL_Flip(screen);
                        //applysettings
                    }
                    if (x >= 1208 && x <= 1221 && y >= 386 && y <= 477)
                    {
                        if (Mix_PlayChannel(-1, scratch, 0) == -1)
                        {
                            return 1;
                        }
                        volume = 100;
                        Mix_VolumeMusic(volume);
                        show_settings();
                        SDL_Flip(screen);
                        //applysettings
                    }
                }
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_j)
                    {
                        if (actpos_previous == 1)
                            show_menu();
                        actpos = actpos_previous;
                    }
                    if (event.key.keysym.sym == SDLK_g)
                    {
                        //If there is no music playing
                        if (Mix_PlayingMusic() == 0)
                        {
                            //Play the music
                            if (Mix_PlayMusic(music, -1) == -1)
                            {
                                return 1;
                            }
                        }
                        //If music is being played
                        else
                        {
                            //If the music is paused
                            if (Mix_PausedMusic() == 1)
                            {
                                //Resume the music
                                Mix_ResumeMusic();
                            }
                            //If the music is playing
                            else
                            {
                                //Pause the music
                                Mix_PauseMusic();
                            }
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_c)
                    {
                        //Stop the music
                        Mix_HaltMusic();
                    }
                }
                if (event.type == SDL_QUIT)
                    quit = 1;
            }
        }
    }
    return 0;
}

void show_settings()
{
    afficher_ecran(584, 164, settings, screen);
    afficher_ecran(776, 779, donebtn_u, screen);
    FillRect(1207,370,14,87,0x979797);
    FillRect(1187,370,14,87,0x979797);
    FillRect(1167,370,14,87,0x979797);
    FillRect(1147,370,14,87,0x979797);
    FillRect(1127,370,14,87,0x979797);
    FillRect(1107,370,14,87,0x979797);
switch(volume){
    case 100: FillRect(1207,370,14,87,0x134908);
    case 83: FillRect(1187,370,14,87,0x134908);
    case 67: FillRect(1167,370,14,87,0x134908);
    case 51: FillRect(1147,370,14,87,0x134908);
    case 35: FillRect(1127,370,14,87,0x134908);
    case 19: FillRect(1107,370,14,87,0x134908);
    break;
    }
}

void finprog()
{

    Mix_FreeChunk(scratch);

    SDL_FreeSurface(background);

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
    //Quit SDL
    SDL_Quit();
}
