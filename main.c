#include "gamehead.h"


int main(int argc, char *args[])
{
	SDL_Surface *screen = NULL;
	menuitems MI;
	pauseitems PI;
	gameitems GI;
	settingsitems SI;
	misc M;
	btn B;
	//Initializing SDL Lib
	screen = init(&M);
	if (screen == NULL)
		return 1;
	//Loading images, texts and sounds into the RAMemory
	if (load_files(&B, &MI,&PI,&GI,&SI,&M) == 0)
		return 1;
	if (load_clips(&M,&MI) == 0)
		return 0;
	//Blitting images, texts, and playing sounds whilst managing motion and clicking events
	//If returned value is 1, we can not continue execution.

	if (afficher_menu(&B,&MI,&GI,&SI,&PI,&M,screen) == 1)
		return 1;
	finprog(&B, &MI,&GI,&SI,&PI,&M,screen);
	return 0;
}
