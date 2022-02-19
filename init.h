#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "gamehead.h"

SDL_Surface *init(misc *M);
int load_files(btn * B, menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M);
int load_clips(misc *M,menuitems *MI);

#endif