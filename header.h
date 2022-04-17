#ifndef HEADER
#define HEADER
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_BPP 32
#define GAME_NAME "Game"

void Init();
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
void LoadImages();
void loadMainMenu(int *ActiveScreen, int *quit);
void loadGame(int *ActiveScreen, int *quit);
void LoadAudio();
int drawText(SDL_Surface *screen, SDL_Surface *textSurface, char string[], int size, int x, int y, int fR, int fG, int fB);
void loadCredit(int *ActiveScreen, int *quit);
void loadSettings(int *ActiveScreen, int *quit);
void Quit();

#endif /* HEADER */
