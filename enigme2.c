#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "en.h"
Mix_Chunk *click = NULL;
SDL_Surface *hero = NULL;
SDL_Surface *cons = NULL;

int volume = 100;

void init_enigme2(enigme2 *e)
{
	int i, w;

	e->p.x = 0;
	e->p.y = 0;
	e->img = NULL;
	e->animation.SpriteSheet = IMG_Load("images/clock.png");
	e->animation.pos.x = 0;
	e->animation.pos.y = 0;
	e->animation.frames = 5;

	for (i = 0, w = 0; i < e->animation.frames; i++, w += 500)
	{
		e->animation.Clips[i].w = 400;
		e->animation.Clips[i].h = 450;
		e->animation.Clips[i].x = w;
		e->animation.Clips[i].y = 0;
	}
	click = Mix_LoadWAV("sounds/scratch.wav");
	if (click == NULL)
	{
		return;
	}
}

void generate_afficher(SDL_Surface *screen, char image[], enigme2 *e, int *alea)
{
	int test = *alea;
	int i = 0;
	FILE *f;
	f = fopen("en.txt", "r");
	do
	{
		*alea = 1 + rand() % 3;
	} while (*alea == test);
	while (fscanf(f, "%s %d\n", image, &(*e).reponse_juste) != EOF && i != *alea)
		i++;

	e->img = IMG_Load(image);
	SDL_BlitSurface(e->img, NULL, screen, &(e->p));
	SDL_Flip(screen);
}

int resolution(int *running, int *run)
{
	SDL_Event event;
	int r = 0;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		*running = 0;
		*run = 0;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			r = 1;
			break;
		case SDLK_b:
			r = 2;
			break;
		case SDLK_c:
			r = 3;
			break;
		}
		break;
	}
	return r;
}

void afficher_resultat(SDL_Surface *screen, int r, enigme2 *en)
{

	if (r == 1)
	{
		en->img = IMG_Load("images/win.jpg");
		SDL_BlitSurface(en->img, NULL, screen, &(en->p));
		SDL_Flip(screen);
	}
	else
	{
		en->img = IMG_Load("images/lose.jpg");
		SDL_BlitSurface(en->img, NULL, screen, &(en->p));
		SDL_Flip(screen);
	}
}

void character2(SDL_Surface *screen, int *choice)
{
	SDL_Event event;

	SDL_Surface *daddou, *lassaad;
	daddou = IMG_Load("images/daddou.png");
	lassaad = IMG_Load("images/lassaad.png");

	SDL_Rect daddou_pos, lassaad_pos;

	daddou_pos.x = 800;
	daddou_pos.y = 200;

	lassaad_pos.x = 0;
	lassaad_pos.y = 200;

	SDL_BlitSurface(daddou, NULL, screen, &daddou_pos);
	SDL_BlitSurface(lassaad, NULL, screen, &lassaad_pos);
	SDL_Flip(screen);

	SDL_WaitEvent(&event);

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.x >= daddou_pos.x && event.button.x <= daddou_pos.x + 103 && event.button.y >= daddou_pos.y && event.button.y <= daddou_pos.y + 376)
			*choice = 1;

		if (event.button.x >= lassaad_pos.x && event.button.x <= lassaad_pos.x + 472 && event.button.y >= lassaad_pos.y && event.button.y <= lassaad_pos.y + 615)
			*choice = 2;
	}
}

void controller(SDL_Surface *screen, int *choice)
{

	SDL_Event event;

	SDL_Surface *keyboard, *controller;
	keyboard = IMG_Load("images/keyboard.jpg");
	controller = IMG_Load("images/controller.jpg");

	SDL_Rect keyboard_pos, controller_pos;

	keyboard_pos.x = 800;
	keyboard_pos.y = 200;

	controller_pos.x = 0;
	controller_pos.y = 200;

	SDL_BlitSurface(keyboard, NULL, screen, &keyboard_pos);
	SDL_BlitSurface(controller, NULL, screen, &controller_pos);
	SDL_Flip(screen);

	SDL_WaitEvent(&event);

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.x >= keyboard_pos.x && event.button.x <= keyboard_pos.x + 360 && event.button.y >= keyboard_pos.y && event.button.y <= keyboard_pos.y + 360)
			*choice = 1;

		if (event.button.x >= controller_pos.x && event.button.x <= controller_pos.x + 800 && event.button.y >= controller_pos.y && event.button.y <= controller_pos.y + 800)
			*choice = 2;
	}
}
