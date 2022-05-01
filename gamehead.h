/**
 * @file gamehead.h
 * @author 
 * Abdelmalek Amir Hassen
 * Yasmine Ayadi
 * Yassine Bouzouita
 * Mohamed Sghaier Chaaben
 * Nour Mbarki
 * Akkari Rihem
 * @brief This a header that collects all the headers and calls them all at once
 * @version 0.7
 * @date 2022-04-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GAMEHEAD_H_INCLUDED
#define GAMEHEAD_H_INCLUDED
#define SCREEN_BBP 32
#define FRAMES_PER_SECOND 22
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>
#include "ninjahubstd.h"
#include "es.h"
#include "timer.h"

#include "gamestructs.h"
#include "character.h"
#include "background.h"
#include "init.h"
#include "enigme.h"
#include "affichage.h"



/**
 * @brief Afficher Menu is a function that starts the entire Video Game
 * 
 * @param BD Button Dimentions are stored in here
 * @param B  Button SDL_Surfaces are stored in here
 * @param MI Menu Items are stored in here
 * @param GI Game Items are stored in here
 * @param SI Settings Items are stored in here
 * @param PI Pause Menu Items are stored in here
 * @param M Miscalenous items such as Sound are stored in here
 * @param p Character and it's specifications are stored in here
 * @param en Enemy specifications are stored in here
 * @param b Background and its characteristics are stored in here
 * @param screen The Screen SDL_Surface
 * @return 0 For quitting 1 For Exception Thrown
 */


int afficher_menu(btndim *BD,btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, character *popt, Ennemi *en, background *b, SDL_Surface *screen);

/**
 * @brief FinProg is a function that frees Most of the loaded items especially from the menu
 * 
 * @param B Button SDL_Surfaces to free
 * @param MI Menu Items to free
 * @param GI GameItems to free
 * @param SI SettingsItems to free
 * @param PI Pause Items to free
 * @param M Miscalenous Items to free
 * @param p Character items to free
 * @param screen Screen that we will free
 */
void finprog(btn *B,menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, character *popt, SDL_Surface *screen);
#endif // MENU_H_INCLUDED
