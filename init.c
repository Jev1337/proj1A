

#include "gamehead.h"

/**
 * @brief
 * This function Initializes SDL Library
 * @param M we need M to save the SCREEN WIDTH and SCREEN HEIGHT on
 * @return SDL_Surface* which is the screen
 */
SDL_Surface *init(misc *M)
{

    SDL_Surface *screen;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return NULL;
    }
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    M->SCREEN_H = info->current_h;
    M->SCREEN_W = info->current_w;
    screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    SDL_EnableKeyRepeat(1, 1);
    if (TTF_Init() == -1)
    {
        return NULL;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 128) == -1)
    {
        return NULL;
    }
    SDL_WM_SetCaption("AR:T", NULL);
    return screen;
}

void MI_Init(menuitems *MI)
{

    MI->background = load_image("images/Menu.png");
    MI->credits = IMG_Load("images/credits.png");
    MI->btnreset = IMG_Load("images/menureset.png");
    MI->rainspr = IMG_Load("images/rainsh.png");
    MI->lvl = 0;
}

void SI_Init(settingsitems *SI)
{
    SI->volume[0] = IMG_Load("images/vol1.png");
    SI->volume[1] = IMG_Load("images/vol2.png");
    SI->volume[2] = IMG_Load("images/vol3.png");
    SI->volume[3] = IMG_Load("images/vol4.png");
    SI->volume[4] = IMG_Load("images/vol5.png");
    SI->volume[5] = IMG_Load("images/vol6.png");
    SI->settings = IMG_Load("images/settings.png");

}

void GI_Init(gameitems *GI)
{
    GI->SecOpt = 0;
    GI->lvl = 0;
    GI->zoomable = IMG_Load("images/Red(LevelOne)minimapBIG.png");
    GI->heart = IMG_Load("images/heartsheets.png");
    GI->LoadSave = 1;
    GI->egg = IMG_Load("images/eggsheet.png");
    GI->eggstat = -1;
    GI->eshealth = 3;
}

void B_Init(btn *B)
{
    B->menubtns_u[2] = IMG_Load("images/quitbtn_u.png");
    B->menubtns_s[2] = IMG_Load("images/quitbtn_s.png");
    B->menubtns_u[1] = IMG_Load("images/creditsbtn_u.png");
    B->menubtns_s[1] = IMG_Load("images/creditsbtn_s.png");
    B->menubtns_u[0] = IMG_Load("images/continuebtn_u.png");
    B->menubtns_s[0] = IMG_Load("images/continuebtn_s.png");
    B->resumebtn[0] = IMG_Load("images/resumebtn_u.png");
    B->resumebtn[1] = IMG_Load("images/resumebtn_s.png");
    B->settingsbtnreal[0] = IMG_Load("images/settingsbtnreal_u.png");
    B->settingsbtnreal[1] = IMG_Load("images/settingsbtnreal_s.png");
    B->donebtn[0] = IMG_Load("images/done_u.png");
    B->donebtn[1] = IMG_Load("images/donebtn_s.png");
    B->menubtns_u[4] = IMG_Load("images/newgamebtn_u.png");
    B->menubtns_s[4] = IMG_Load("images/newgamebtn_s.png");
    B->menubtns_u[3] = IMG_Load("images/optionbtn_u.png");
    B->menubtns_s[3] = IMG_Load("images/optionbtn_s.png");
    B->fsbtn[0] = IMG_Load("images/FullScreenSettings.png");
    B->fsbtn[1] = IMG_Load("images/WindowedDebugSettings.png");
    B->fsbtn[2] = IMG_Load("images/WindowedSettings.png");
    B->menubtns_ss[0] = IMG_Load("images/continuebtn_ss.png");
    B->menubtns_ss[1] = IMG_Load("images/menuresetuu.png");
    B->menubtns_ss[2] = IMG_Load("images/quitbtn_ss.png");
    B->menubtns_ss[3] = IMG_Load("images/optionbtn_ss.png");
    B->menubtns_ss[4] = IMG_Load("images/newgame_ss.png");

    B->isselected[0] = 0;
    B->isselected[1] = 0;
    B->isselected[2] = 0;
    B->isselected[3] = 0;
    B->isselected[4] = 0;
    B->isselected[5] = 0;
    B->isselected[6] = 0;
    B->isselected[7] = 0;
    B->isselected[8] = 0;
}

void M_Init(misc *M){
        M->music = Mix_LoadMUS("sounds/beat.mp3");
    M->scratch = Mix_LoadWAV("sounds/scratch.wav");
    M->font = TTF_OpenFont("fonts/Retro.ttf", 48);
    M->fontBig = TTF_OpenFont("fonts/Retro.ttf", 26);
    M->volume = 128;
    M->volumeSFX = 128;
    M->cooldown = IMG_Load("images/cooldown.png");
    M->cldw = 4;
}

void PI_Init(pauseitems *PI){
    PI->pausemenu = IMG_Load("images/pausemenu.png");
    PI->run=Mix_LoadWAV("sounds/running.wav");
    PI->mvmt=0;
    PI->mvmt2=0;
    PI->throw = Mix_LoadWAV("sounds/throw.wav");
}

/**
 * @brief
 *
 * @param BD a struct that has some of the button dimentions in it
 * @param B a struct that contains the SDL_Surface of the buttons
 * @param MI a struct that contains Menu Items
 * @param PI a struct that contains Pause Menu Items
 * @param GI a struct that contains Game Items
 * @param SI a struct that contains Settings Items
 * @param M a struct that contains Miscalenous items
 * @param p a struct that contains character specifications
 * @return int (1 For Good 0 for Error)
 */
int load_files(btndim *BD, btn *B, menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M, character *p, character *popt)
{

    SDL_Color white = {255, 255, 255};

    BD->menubtns[2].x = 58;
    BD->menubtns[2].y = 867;

    BD->menubtns[1].x = 58;
    BD->menubtns[1].y = 680;

    BD->menubtns[0].x = 58;
    BD->menubtns[0].y = 337;

    BD->menubtns[4].x = 58;
    BD->menubtns[4].y = 527;

    BD->menubtns[3].x = 58;
    BD->menubtns[3].y = 697;

    BD->resumebtn.x = 760;
    BD->resumebtn.y = 413;
    BD->resumebtn.w = 400;
    BD->resumebtn.h = 110;
    BD->settingsbtnreal.x = 760;
    BD->settingsbtnreal.y = 540;
    BD->settingsbtnreal.w = 400;
    BD->settingsbtnreal.h = 110;
    BD->donebtn.x = 1345;
    BD->donebtn.y = 867;

    BD->fsbtn.x = 1201;
    BD->fsbtn.y = 612;

    BD->menubtns[2].w = B->menubtns_s[2]->w;
    BD->menubtns[2].h = B->menubtns_s[2]->h;

    BD->menubtns[1].w = B->menubtns_s[1]->w;
    BD->menubtns[1].h = B->menubtns_s[1]->h;

    BD->menubtns[0].w = B->menubtns_s[0]->w;
    BD->menubtns[0].h = B->menubtns_s[0]->h;

    BD->menubtns[4].w = B->menubtns_s[4]->w;
    BD->menubtns[4].h = B->menubtns_s[4]->h;

    BD->menubtns[3].w = B->menubtns_s[3]->w;
    BD->menubtns[3].h = B->menubtns_s[3]->h;

    BD->donebtn.w = B->donebtn[1]->w;
    BD->donebtn.h = B->donebtn[1]->h;

    BD->fsbtn.w = B->fsbtn[1]->w;
    BD->fsbtn.h = B->fsbtn[1]->h;


    MI->gamename = TTF_RenderText_Solid(M->font, "AR:T", white);
    MI->leftarrow = TTF_RenderText_Solid(M->fontBig, ">", white);
    MI->rightarrow = TTF_RenderText_Solid(M->fontBig, "<", white);

    

    if (MI->rightarrow == NULL || MI->leftarrow == NULL || MI->rainspr == NULL || MI->gamename == NULL || B->fsbtn[0] == NULL || B->fsbtn[1] == NULL || B->fsbtn[2] == NULL || M->music == NULL || M->font == NULL || M->scratch == NULL || SI->settings == NULL || MI->background == NULL || B->menubtns_u[2] == NULL || B->menubtns_u[1] == NULL || B->menubtns_u[0] == NULL || B->menubtns_u[4] == NULL || B->menubtns_u[3] == NULL || B->donebtn[1] == NULL || B->donebtn[0] == NULL || B->menubtns_s[2] == NULL || B->menubtns_s[1] == NULL || B->menubtns_s[0] == NULL || B->menubtns_s[4] == NULL || B->menubtns_s[3] == NULL || B->donebtn[1] == NULL || B->donebtn[0] == NULL || PI->pausemenu == NULL || B->settingsbtnreal[1] == NULL || B->settingsbtnreal[0] == NULL || B->resumebtn[1] == NULL || B->resumebtn[0] == NULL)
    {
        return 0;
    }
    return 1;
}

/**
 * @brief This function allows us to use split a spritesheet into multiple clips
 *
 * @param M Miscalenous that has Screen Width and Screen Height stored in it
 * @param MI Menu Items because we need to store the rain clips into it
 * @param p The character also has sprite sheets, therefore we need to split the pictures
 * @return int (1 for OK) This function could be void too there is no difference
 */

int load_clips(misc *M, menuitems *MI, gameitems *GI, character *p, character *popt)
{
    int i, w;
    for (w = M->SCREEN_W, i = 0; i < 8; i++, w += M->SCREEN_W)
    {
        MI->rainclip[i].x = w;
        MI->rainclip[i].y = 0;
        MI->rainclip[i].w = M->SCREEN_W;
        MI->rainclip[i].h = M->SCREEN_H;
    }
    for (w = 0, i = 0; i < 4; i++, w += 366)
    {
        p->clips[i].x = w;
        p->clips[i].y = 0;
        p->clips[i].w = 366;
        p->clips[i].h = 484;
    }
    for (w = 0, i = 0; i < 4; i++, w += 366)
    {
        popt->clips[i].x = w;
        popt->clips[i].y = 0;
        popt->clips[i].w = 366;
        popt->clips[i].h = 484;
    }
    for (w = 0, i = 0; i < 5; i++, w += 44)
    {
        GI->heartClip[i].x = w;
        GI->heartClip[i].y = 0;
        GI->heartClip[i].w = 44;
        GI->heartClip[i].h = 44;
    }
    for (w = 0, i = 0; i < 8; i++, w += 100.25)
    {
        GI->eggsheet[i].x = w;
        GI->eggsheet[i].y = 0;
        GI->eggsheet[i].w = 100.25;
        GI->eggsheet[i].h = 128;
    }
    for (w = 0, i = 0; i < 5; i++, w += 171)
    {
        M->cooldownsheet[i].x = w;
        M->cooldownsheet[i].y = 0;
        M->cooldownsheet[i].w = 171;
        M->cooldownsheet[i].h = 27;
    }

    return 1;
}