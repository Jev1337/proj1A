
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <time.h>

SDL_Surface *load_image(char filename[])
{

    //Temporary storage for the image that's loaded
    SDL_Surface *loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface *optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load(filename);
    //If nothing went wrong in loading the image
    if (loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);
    }
    //Return the optimized image
    return optimizedImage;
}
void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{

    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface(src, NULL, dest, &offset);
}

void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(screen, &rect, color);
}