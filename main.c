/*This source code copyrighted by NinjaHub' Studios (2021-2022)
and may not be redistributed without written permission.*/

//Using SDL (SDL Itself + SDL TTF) and standard IO

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "gamehead.h"


int main(int argc, char *args[])
{
	SDL_Surface *screen = NULL;
	menuitems MI;
	pauseitems PI;
	gameitems GI;
	settingsitems SI;
	misc M;
	//Initializing SDL Lib
	screen = init();
	if (screen == NULL)
		return 1;
	//Loading images, texts and sounds into the RAMemory
	if (load_files(&MI,&PI,&GI,&SI,&M) == 0)
		return 1;
	//Blitting images, texts, and playing sounds whilst managing motion and clicking events
	//If returned value is 1, we can not continue execution.

	if (afficher_menu(&MI,&GI,&SI,&PI,&M,screen) == 1)
		return 1;
	finprog(&MI,&GI,&SI,&PI,&M,screen);
	return 0;
}
