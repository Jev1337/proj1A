#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>

typedef struct
{
    SDL_Surface *SpriteSheet;
    SDL_Rect pos;
    SDL_Rect Clips[5];
    int frames;
    int ClipLoaded;
} animation2;
typedef struct
{
    SDL_Surface *img; 
    SDL_Rect p;
    int reponse_juste;
    int reponse;
    animation2 animation;
} enigme2;

void init_enigme2(enigme2 *e);
void generate_afficher(SDL_Surface *screen, char image[], enigme2 *e, int *alea);
int resolution(int *running, int *run);
void afficher_resultat(SDL_Surface *screen, int r, enigme2 *en);