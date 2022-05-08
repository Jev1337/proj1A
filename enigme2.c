#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "en.h"

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
