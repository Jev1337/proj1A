#include "background.h"

void init_bg(background *b, int x)
{
  b->image = IMG_Load("images/Red(LevelOne).png");
  b->imageM = IMG_Load("images/Red(LevelOne)Mask.png");
    b->image2 = IMG_Load("images/Red(LevelOne).png");
  b->imageM2 = IMG_Load("images/Red(LevelOne)Mask.png");
  
  b->posimage.y = 0;
  b->posmask.y = 1080 - 484;
  b->posmask.w = 300;
  b->posmask.h = 484;

    b->posimage.x = 0;
    b->posimage.w = 1920;
    b->posimage.h = 1080;
    b->posmask.x = 0;

    b->posimage2.y = 0;
    b->posmask2.y = 1080 - 484;
    b->posmask2.w = 300;
    b->posmask2.h = 484;
    b->posimage2.x = 0;
    b->posimage2.w = 1920/2;
    b->posimage2.h = 1080;
    b->posmask2.x = 0;


}

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
  SDL_Color color;
  Uint32 col = 0;
  char *pPosition = (char *)pSurface->pixels;
  pPosition += (pSurface->pitch * y);
  pPosition += (pSurface->format->BytesPerPixel * x);
  memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
  SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
  return (color);
}

int collisionPP(SDL_Rect p, SDL_Surface *Masque)
{
  SDL_Color colobs;
  SDL_Color colgotten;
  SDL_Rect Pos[8];
  int i = 0;
  colobs.r = 255;
  colobs.g = 255;
  colobs.b = 255;
  Pos[0].x = p.x;
  Pos[0].y = p.y;
  Pos[1].x = p.x + (p.w / 2);
  Pos[1].y = p.y;
  Pos[2].x = p.x + p.w;
  Pos[2].y = p.y;
  Pos[3].x = p.x;
  Pos[3].y = p.y + (p.h / 2);
  Pos[4].x = p.x;
  Pos[4].y = p.y + p.h;
  Pos[5].x = p.x + (p.w / 2);
  Pos[5].y = p.y + p.h;
  Pos[6].x = p.x + p.w;
  Pos[6].y = p.y + p.h;
  Pos[7].x = p.x + p.w;
  Pos[7].y = p.y + (p.h / 2);
  while ((i <= 7))
  {
    colgotten = GetPixel(Masque, Pos[i].x, Pos[i].y);
    printf("position %d- x: %d y: %d R:%d G:%d B:%d\n", i, Pos[i].x, Pos[i].y, colgotten.r, colgotten.g, colgotten.b);
    if ((colobs.r == colgotten.r) && (colobs.b == colgotten.b) && (colobs.g == colgotten.g))
      return 1;
    else
      i++;
  }
  return 0;
}
