/**
 * @file gamestructs.h
 * @author 
 * Abdelmalek Amir Hassen
 * Yasmine Ayadi
 * Yassine Bouzouita
 * Mohamed Sghaier Chaaben
 * Nour Mbarki
 * Akkari Rihem
 * @brief This Header File has most of the Menu Structs that we will need to store the SDL_Surfaces on them
 * @version 0.7
 * @date 2022-04-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GAMESTRUCTS_H_INCLUDED
#define GAMESTRUCTS_H_INCLUDED
#include "gamehead.h"

/**
 * @struct btndim
 * @brief This struct allows us to store button dimentions for optimization reasons
 */
typedef struct{

    SDL_Rect menubtns[5]; /*!< Menu Buttons*/
    SDL_Rect donebtn; /*!< Shared Done Button*/
    SDL_Rect resumebtn; /*!< Resume Button*/
    SDL_Rect settingsbtnreal; /*!< Bigger Settings Button*/
    SDL_Rect fsbtn; /*!< Fs Button*/

}btndim;

/**
 * @struct btn
 * @brief This struct allows us to store buttons in SDL_Surface and their status
 */
typedef struct{
    SDL_Surface *menubtns_u[5]; /*!< Menu Buttons that are unselected loaded in SDL_Surface*/
    SDL_Surface *menubtns_s[5]; /*!< Menu Buttons that are selected loaded in SDL_Surface*/
    SDL_Surface *resumebtn[2]; /*!< Resume Button (0 is unselected, 1 is selected) loaded in SDL_Surface*/
    SDL_Surface *settingsbtnreal[2]; /*!< Settings Button (0 is unselected, 1 is selected) loaded in SDL_Surface*/
    SDL_Surface *donebtn[2]; /*!< Shared Done BUtton (0 is unselected, 1 is selected) loaded in SDL_Surface*/
    SDL_Surface *fsbtn[3]; /*!< Fs Button loaded in SDL_Surface*/

    int isselected[9]; /*!< Button Selection Status*/
}btn;

/**
 * @struct menuitems
 * @brief This struct allows us to store some additional buttons in SDL_Surface
 */
typedef struct{
    SDL_Surface *background; /*!< Background Image loaded in SDL_Surface*/
    SDL_Surface *credits; /*!< Credits Image loaded in SDL_Surface*/
    SDL_Surface *gitbtn_s; /*!< Github Button Image loaded in SDL_Surface*/
    SDL_Surface *leftarrow; /*!< BLeft Arrow Image loaded in SDL_Surface*/
    SDL_Surface *rightarrow; /*!< Right Arrow Image loaded in SDL_Surface*/
    SDL_Surface *btnreset; /*!< Menu Layout Reset Image loaded in SDL_Surface*/
    SDL_Surface *rainspr;  /*!< Rain Spritesheet loaded in SDL_Surface*/
    SDL_Surface *gamename; /*!< Game Name Image loaded in SDL_Surface*/
    SDL_Rect rainclip[8]; /*!< Rain Clips Coordinates Initialized in SDL_Rect*/
}menuitems;

/**
 * @struct gameitems
 * @brief This struct allows us to store things that we cannot store in other structures
 */
typedef struct{
    int lvl; /*!< Level is stored in the GameItems*/
    int SecOpt;
    int LoadSave;
    SDL_Surface *zoomable;
    SDL_Surface *heart;
    SDL_Rect heartClip[5];
}gameitems;

/**
 * @struct pauseitems
 * @brief This struct allows us to store pause menu in SDL_Surface
 */
typedef struct{
    SDL_Surface *pausemenu; /*!< Pause Menu Image loaded in SDL_Surface*/
}pauseitems;
/**
 * @struct settingsitems
 * @brief This struct allows us to store settings buttons in SDL_Surface and their status
 */
typedef struct{
    SDL_Surface *settings; /*!< Settings Image loaded in SDL_Surface*/
    SDL_Surface *volume[6];
}settingsitems;

/**
 * @struct misc
 * @brief This struct allows us to misc things that we may need but are mostly optional
 */
typedef struct{
    Mix_Music *music; /*!< Continious Music Loaded in Mix_Music*/
    Mix_Chunk *scratch; /*!< On click sound Loaded in Mix_Chunk*/
    TTF_Font *font; /*!< Font Loaded in TTF_Font*/
    TTF_Font *fontBig; /*!< Bigger Font Loaded in TTF_Font*/
    int SCREEN_W; /*!< The Actual Screen Width is stored here*/
    int SCREEN_H; /*!< The Actual Screen Height is stored here*/
    int volume; /*!< Volume loaded in SDL_Surface*/
    int volumeSFX;

}misc;

#endif