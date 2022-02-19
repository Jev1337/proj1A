
#include "gamehead.h"


SDL_Surface *init(misc *M)
{

    SDL_Surface *screen;
    // Initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return NULL;
    }
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    M->SCREEN_H = info->current_h;
    M->SCREEN_W = info->current_w;
    // Set up the screen
    screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE | SDL_FULLSCREEN);

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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 128) == -1)
    {
        return NULL;
    }
    // Set the window caption
    SDL_WM_SetCaption("AR:T", NULL);

    // If everything initialized fine
    return screen;
}


int load_files(btn *B,menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M)
{
   
    SDL_Color white = {255, 255, 255};


    //Due to a problem, I am not able to initialize 
    B->quitbtn[0] = IMG_Load("images/exitbtn_u.png");
    B->quitbtn[1] = IMG_Load("images/exitbtn_s.png");
    B->creditsbtn[0] = IMG_Load("images/creditsbtn_u.png");
    B->creditsbtn[1] = IMG_Load("images/creditsbtn_s.png");
    B->continuebtn[0] = IMG_Load("images/continuebtn_u.png");
    B->continuebtn[1] = IMG_Load("images/continuebtn_s.png");
    B->gitbtn[0] = IMG_Load("images/gitbtn_u.png");
    B->gitbtn[1] = IMG_Load("images/gitbtn_s.png");
    B->settingsbtn[0] = IMG_Load("images/settingsbtn_u.png");
    B->settingsbtn[1] = IMG_Load("images/settingsbtn_s.png");
    B->resumebtn[0] = IMG_Load("images/resumebtn_u.png");
    B->resumebtn[1] = IMG_Load("images/resumebtn_s.png");
    B->settingsbtnreal[0] = IMG_Load("images/settingsbtnreal_u.png");
    B->settingsbtnreal[1] = IMG_Load("images/settingsbtnreal_s.png");
    B->donebtn[0] = IMG_Load("images/done_u.png");
    B->donebtn[1] = IMG_Load("images/done_s.png");
    B->fsbtn[0]= IMG_Load("images/fsbtn_u.png");
    B->fsbtn[1] = IMG_Load("images/fsbtn_s1.png");
    B->fsbtn[2] = IMG_Load("images/fsbtn_s2.png");
    B->isselected[0] = 0;
    B->isselected[1] = 0;
    B->isselected[2] = 0;
    B->isselected[3] = 0;
    B->isselected[4] = 0;
    B->isselected[5] = 0;
    B->isselected[6] = 0;
    B->isselected[7] = 0;
    B->isselected[8] = 0;

    MI->background = load_image("images/background.png");
    MI->credits = IMG_Load("images/credits.png");
    MI->btnreset = IMG_Load("images/btnreset.png");
    MI->rainspr = IMG_Load("images/rainsh.png");

    M->music = Mix_LoadMUS("sounds/beat.mp3");
    M->scratch = Mix_LoadWAV("sounds/scratch.wav");
    M->font = TTF_OpenFont("fonts/Retro.ttf", 48);
    M->fontBig = TTF_OpenFont("fonts/Retro.ttf", 72);
    M->volume = 128;

    MI->gamename = TTF_RenderText_Solid(M->font, "AR:T", white);
    MI->leftarrow = TTF_RenderText_Solid(M->fontBig, ">", white);
    MI->rightarrow = TTF_RenderText_Solid(M->fontBig, "<", white);

    GI->gamebackground = load_image("images/gamebackground.png");
    SI->settings = IMG_Load("images/settings.png");


    

    PI->pausemenu = IMG_Load("images/pausemenu.png");



    
    if (MI->rightarrow == NULL || MI->leftarrow == NULL || MI->rainspr == NULL || MI->gamename == NULL || B->fsbtn[0] == NULL || B->fsbtn[1] == NULL || B->fsbtn[2] == NULL || M->music == NULL || M->font == NULL || M->scratch == NULL || SI->settings == NULL || MI->background == NULL || B->quitbtn[0] == NULL || B->creditsbtn[0] == NULL || B->continuebtn[0] == NULL || B->gitbtn[0] == NULL || B->settingsbtn[0] == NULL || B->quitbtn[1] == NULL || B->creditsbtn[1] == NULL || B->continuebtn[1] == NULL || B->gitbtn[1] == NULL || B->settingsbtn[1] == NULL || B->donebtn[1] == NULL || B->donebtn[0] == NULL || GI->gamebackground == NULL || PI->pausemenu == NULL || B->settingsbtnreal[1] == NULL || B->settingsbtnreal[0] == NULL || B->resumebtn[1] == NULL || B->resumebtn[0] == NULL)
    {
        return 0;
    }
    // If everything loaded fine
    return 1;
    
}


int load_clips(misc *M, menuitems *MI){
    int i, w=M->SCREEN_W;
    for (i=0;i<8;i++, w+=M->SCREEN_W){
        MI->rainclip[i].x = w;
        MI->rainclip[i].y = 0;
        MI->rainclip[i].w = M->SCREEN_W;
        MI->rainclip[i].h = M->SCREEN_H;
    }
    return 1;
}