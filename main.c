#include "gamehead.h"
#include "time.h"

int main(int argc, char *args[])
{
	SDL_Surface *screen = NULL;
	menuitems MI;
	pauseitems PI;
	gameitems GI;
	settingsitems SI;
	misc M;
	btn B;
	btndim BD;
	character p;
	Ennemi e;
	srand(time(NULL));
	
	//Initializing SDL Lib
	screen = init(&M);
	if (screen == NULL)
		return 1;
	//Loading images, texts and sounds into the RAMemory
	if (load_files(&BD, &B, &MI,&PI,&GI,&SI,&M, &p) == 0)
		return 1;
	if (load_clips(&M,&MI, &p) == 0)
		return 0;
	//Blitting images, texts, and playing sounds whilst managing motion and clicking events
	//If returned value is 1, we can not continue execution.

	if (afficher_menu(&BD,&B,&MI,&GI,&SI,&PI,&M,&p,&e,screen) == 1)
		return 1;
	finprog(&B, &MI,&GI,&SI,&PI,&M,&p,screen);
	return 0;
}
