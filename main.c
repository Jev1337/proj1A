/**
 * @file main.c
 * @author 
 * Abdelmalek Amir Hassen
 * Yasmine Ayadi
 * Yassine Bouzouita
 * Mohamed Sghaier Chaaben
 * Nour Mbarki
 * Akkari Rihem
 * @brief 
 * This is the main.c of an SDL 1.2 Game (Yes Outdated) for our School Project (ESPRIT 1A)
 * @version 0.7
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gamehead.h"
#include "time.h"

/**
 * @brief main function
 * 
 * @param argc Obligatory Call
 * @param args Obligatory Call
 * @return Returning 1 Means a problem has occured and Returning 0 Means a program went well
 */
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
	character popt;
	Ennemi e;
	background b;
	
	srand(time(NULL));
	screen = init(&M);

	//system("stty -F /dev/ttyUSB0 9600 -parenb cs8 -cstopb");
	if (screen == NULL)
		return 1;
	MI_Init(&MI);
	SI_Init(&SI);
	B_Init(&B);
	GI.SecOpt = 0;
	GI.lvl = 0;
	GI.zoomable = IMG_Load("images/Red(LevelOne)minimapBIG.png");
	GI.heart = IMG_Load("images/heartsheets.png");
	GI.LoadSave = 1;
	if (GI.SecOpt)
		GI.LoadSave = 0;
	if (load_files(&BD, &B, &MI,&PI,&GI,&SI,&M, &p, &popt) == 0)
		return 1;
	if (load_clips(&M,&MI,&GI, &p, &popt) == 0)
		return 0;
	if (afficher_menu(&BD,&B,&MI,&GI,&SI,&PI,&M,&p, &popt,&e,&b, screen) == 1)
		return 1;
	finprog(&B, &MI,&GI,&SI,&PI,&M,&p, &popt,screen);
	return 0;
}
