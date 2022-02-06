/*This source code copyrighted by NinjaHub' Studios (2021-2022)
and may not be redistributed without written permission.*/

//Using SDL (SDL Itself + SDL TTF) and standard IO

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "gamehead.h"


int SWidth = SCREEN_W;
int SHeight = SCREEN_H;
SDL_Surface *screen = NULL;
SDL_Surface *credits = NULL;
SDL_Surface *background= NULL;
SDL_Surface *gamebackground= NULL;
SDL_Surface *pausemenu= NULL;
SDL_Surface *settings= NULL;
SDL_Surface *resumebtn_u= NULL;
SDL_Surface *resumebtn_s= NULL;
SDL_Surface *donebtn_u= NULL;
SDL_Surface *donebtn_s= NULL;
SDL_Surface *quitbtn_u= NULL;
SDL_Surface *quitbtn_s= NULL;
SDL_Surface *creditsbtn_u= NULL;
SDL_Surface *creditsbtn_s= NULL;
SDL_Surface *continuebtn_u= NULL;
SDL_Surface *continuebtn_s= NULL;
SDL_Surface *gitbtn_u= NULL;
SDL_Surface *gitbtn_s= NULL;
SDL_Surface *settingsbtnreal_u= NULL;
SDL_Surface *settingsbtnreal_s= NULL;
SDL_Surface *settingsbtn_u= NULL;
SDL_Surface *settingsbtn_s= NULL;
SDL_Surface *gamenameA= NULL;
SDL_Surface *gamenameB= NULL;
SDL_Surface *leftarrow= NULL;
SDL_Surface *rightarrow= NULL;
Mix_Music *music= NULL;
Mix_Chunk *scratch= NULL;
TTF_Font *fontSmall= NULL;
TTF_Font *font= NULL;
TTF_Font *fontBig= NULL;

int volume= 128,x, y, ccl = 1, continueselected = 0, creditsselected = 0, quitselected = 0, gitselected = 0, settingsselected = 0,
 doneselectedsettings = 0, selectedsettingsreal = 0, selectedresume = 0;

SDL_Event event;
SDL_Color white = {255, 255, 255};
SDL_Color black = {14, 0, 68};

int main(int argc, char *args[])
{
	
	//Initializing SDL Lib
	if (init() == 0)
		return 1;
	//Loading images, texts and sounds into the RAMemory
	if (load_files() == 0)
		return 1;
	//Blitting images, texts, and playing sounds whilst managing motion and clicking events
	//If returned value is 1, we can not continue execution.

	if (afficher_menu() == 1)
		return 1;
	finprog();
	return 0;
}
