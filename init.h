#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "gamehead.h"

SDL_Surface *init(misc *M);
int load_files(btndim *BD ,btn * B, menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M, character *p, character *popt);
int load_clips(misc *M,menuitems *MI,gameitems *GI, character *p, character *popt);
void MI_Init(menuitems *MI);
void SI_Init(settingsitems *SI);
void GI_Init(gameitems *GI);
void B_Init(btn *B);
void M_Init(misc *M);
void PI_Init(pauseitems *PI);
#endif