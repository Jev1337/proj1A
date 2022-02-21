
#include "timer.h"
#define SCREEN_W 1920
#define SCREEN_H 1080
#define SCREEN_BBP 32
#define FRAMES_PER_SECOND 30

// gcc main1.c timer.c -o prog1 -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image

void afficher_ecran(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect *clip)
{

  // Make a temporary rectangle to hold the offsets
  SDL_Rect offset;

  // Give the offsets to the rectangle
  offset.x = x;
  offset.y = y;
  // Blit the surface SDL_BlitSurface (background, NULL, screen, {x,y})
  SDL_BlitSurface(src, clip, dest, &offset);
}

void FillRect(int x, int y, int w, int h, int color, SDL_Surface *screen)
{
  SDL_Rect rect = {x, y, w, h};
  SDL_FillRect(screen, &rect, color);
}

typedef struct
{
  SDL_Surface *background;
  SDL_Surface *btn_u[2];
  SDL_Surface *btn_s[2];
  SDL_Surface *gamename;
  Mix_Music *music;
  Mix_Chunk *scratch;
  int volume;
  TTF_Font *font;
  int isselected[2];
  SDL_Rect btn[2];
} menuobj;

SDL_Surface *init(menuobj *M)
{
  SDL_Surface *screen;
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return NULL;
  }
  /*
  const SDL_VideoInfo *info = SDL_GetVideoInfo();
  int SCREEN_H = info->current_h;
  int SCREEN_W = info->current_w;
  */
  screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);

  if (TTF_Init() == -1)
  {
    return NULL;
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 128) == -1)
  {
    return NULL;
  }
  // Set the window caption
  SDL_WM_SetCaption("AR:T", NULL);
  return screen;
}

int load_files(menuobj *M)
{
  int i;
  SDL_Color white = {255, 255, 255};
  M->btn[0].x = 700;
  M->btn[0].y = 500;
  M->btn[0].w = 400;
  M->btn[0].h = 110;

  M->btn[1].x = 700;
  M->btn[1].y = 700;
  M->btn[1].w = 400;
  M->btn[1].h = 110;

  M->background = IMG_Load("images/gamebackground.jpg");
  M->btn_u[0] = IMG_Load("images/continuebtn_u.png");
  M->btn_u[1] = IMG_Load("images/exitbtn_u.png");
  M->btn_s[0] = IMG_Load("images/continuebtn_s.png");
  M->btn_s[1] = IMG_Load("images/exitbtn_s.png");
  M->music = Mix_LoadMUS("sounds/beat.mp3");
  M->scratch = Mix_LoadWAV("sounds/scratch.wav");
  M->font = TTF_OpenFont("fonts/Retro.ttf", 48);
  M->isselected[0] = 0;
  M->isselected[1] = 0;
  M->gamename = TTF_RenderText_Solid(M->font, "AR:T", white);
  if (M->background == NULL || M->btn_u[0] == NULL || M->btn_s[0] == NULL || M->btn_u[1] == NULL || M->btn_s[1] == NULL || M->music == NULL || M->scratch == NULL ||
      M->font == NULL || M->gamename == NULL)
    return 0;
}

int afficher_menu(menuobj *M, SDL_Surface *screen)
{
  SDL_Event event;
  int frame = 0;
  int cap = 1;
  Timer fps;
  int quit = 0;
  int actpos_previous = 1, actpos = 1;
  int x, y, i;
  if (Mix_PlayMusic(M->music, -1) == -1)
  {
    return 1;
  }

  while (quit == 0)
  {
    start(&fps);
    afficher_ecran(0, 0, M->background, screen, NULL);
    if (M->isselected[0] == 1)
      afficher_ecran(700, 500, M->btn_s[0], screen, NULL);
    else
      afficher_ecran(700, 500, M->btn_u[0], screen, NULL);
    if (M->isselected[1] == 1)
      afficher_ecran(700, 700, M->btn_s[1], screen, NULL);
    else
      afficher_ecran(700, 700, M->btn_u[1], screen, NULL);
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_MOUSEMOTION)
      {
        x = event.motion.x;
        y = event.motion.y;
        for (i = 0; i < 2; i++)
        {
          if (x >= M->btn[i].x && x <= M->btn[i].w + M->btn[i].x && y >= M->btn[i].y && y <= M->btn[i].y + M->btn[i].h)
          {
            if (M->isselected[i] == 0)
            {
              M->isselected[i] = 1;
            }
          }
          else
          {
            if (M->isselected[i] == 1)
            {
              M->isselected[i] = 0;
            }
          }
        }
      }
      if (event.type == SDL_MOUSEBUTTONDOWN)
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          x = event.motion.x;
          y = event.motion.y;
          if (M->isselected[0])
          {
            afficher_ecran(830, 300, M->gamename, screen, NULL);
            if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
            {
              return 1;
            }
          }
          if (M->isselected[1])
          {
            quit = 1;
            if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
            {
              return 1;
            }
          }
        }

      if (event.type == SDL_QUIT)
        quit = 1;
    }
    if (SDL_Flip(screen) == -1)
    {
      return 1;
    }
    // Increment the frame counter
    frame++;
    if ((cap == 1) && (get_ticks(&fps) < 1000 / FRAMES_PER_SECOND))
    {
      // Sleep the remaining frame time
      SDL_Delay((1000 / FRAMES_PER_SECOND) - get_ticks(&fps));
    }
  }
}

void finprog(menuobj *M, SDL_Surface *screen)
{
  Mix_FreeChunk(M->scratch);
  Mix_FreeMusic(M->music);
  SDL_FreeSurface(M->background);
  SDL_FreeSurface(M->btn_s[0]);
  SDL_FreeSurface(M->btn_s[1]);
  SDL_FreeSurface(M->btn_u[0]);
  SDL_FreeSurface(M->btn_u[1]);
  SDL_FreeSurface(M->gamename);
  SDL_FreeSurface(screen);
}

int main(int argc, char *args[])
{

  SDL_Surface *screen = NULL;
  menuobj M;
  screen = init(&M);
  if (screen == NULL)
    return 1;
  if (load_files(&M) == 0)
    return 1;
  if (afficher_menu(&M, screen) == 1)
    return 1;
  finprog(&M, screen);
  return 0;
}
