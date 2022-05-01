#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "gamehead.h"

SDL_Surface *init(misc *M);
int load_files(btndim *BD ,btn * B, menuitems *MI, pauseitems *PI, gameitems *GI, settingsitems *SI, misc *M, character *p, character *popt);
int load_clips(misc *M,menuitems *MI, character *p, character *popt);

#endif