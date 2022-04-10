#include "enigme.h"
#include "string.h"
void afficher_enigme(enigme *e, SDL_Surface *screen)
{

    afficher_ecran(700, 250, e->QM, screen, NULL);
    afficher_ecran(500, 800, e->RSurf, screen, NULL);
    afficher_ecran(600, 840, e->R[0], screen, NULL);
    afficher_ecran(800, 800, e->RSurf, screen, NULL);
    afficher_ecran(900, 840, e->R[1], screen, NULL);
    afficher_ecran(1100, 800, e->RSurf, screen, NULL);
    afficher_ecran(1200, 840, e->R[2], screen, NULL);
    afficher_ecran(960, 330, e->Q, screen, NULL);
}

void animer(enigme *e, SDL_Surface *screen)
{
    SDL_Event event;
    int respon = -1;
    int x, y;
    time_t start;
    SDL_Surface *remaintime = NULL;
    SDL_Surface *resp[2];
    Mix_Chunk *respmus[2];
    resp[0] = IMG_Load("images/correct.png");
    resp[1] = IMG_Load("images/wrong.png");
    respmus[0] = Mix_LoadWAV("sounds/correct.wav");
    respmus[1] = Mix_LoadWAV("sounds/wrong.wav");
    start = time(NULL);
    while (respon == -1 && time(NULL) - start <= 5)
    {
        SDL_Color white = {0, 0, 0};
        switch (time(NULL) - start)
        { 
        case 1:
            remaintime = TTF_RenderText_Solid(e->font, "5", white);
            afficher_enigme(e, screen);
            afficher_ecran(790, 300, remaintime, screen, NULL);
            SDL_Flip(screen);
            break;
        case 2:
            remaintime = TTF_RenderText_Solid(e->font, "4", white);
            afficher_enigme(e, screen);
            afficher_ecran(790, 300, remaintime, screen, NULL);
            SDL_Flip(screen);
            break;
        case 3:
            remaintime = TTF_RenderText_Solid(e->font, "3", white);
            afficher_enigme(e, screen);
            afficher_ecran(790, 300, remaintime, screen, NULL);
            SDL_Flip(screen);
            break;
        case 4:
            remaintime = TTF_RenderText_Solid(e->font, "2", white);
            afficher_enigme(e, screen);
            afficher_ecran(790, 300, remaintime, screen, NULL);
            SDL_Flip(screen);
            break;
        case 5:
            remaintime = TTF_RenderText_Solid(e->font, "1", white);
            afficher_enigme(e, screen);
            afficher_ecran(790, 300, remaintime, screen, NULL);
            SDL_Flip(screen);
            break;
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_1)
                    respon = 1;
                else if (event.key.keysym.sym == SDLK_2)
                    respon = 2;
                else if (event.key.keysym.sym == SDLK_3)
                    respon = 3;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    x = event.button.x;
                    y = event.button.y;
                    if (x >= 600 && x <= 269 + 600 && y >= 840 && y <= 840 + 119)
                    {
                        respon = 1;
                    }
                    if (x >= 900 && x <= 269 + 900 && y >= 840 && y <= 840 + 119)
                    {
                        respon = 2;
                    }
                    if (x >= 1200 && x <= 269 + 1200 && y >= 840 && y <= 840 + 119)
                    {
                        respon = 3;
                    }
                }
            }
        }
    }
    if (respon == e->RJ)
    {
        afficher_ecran(650, 300, resp[0], screen, NULL);
        Mix_PlayChannel(-1, respmus[0], 0);
    }
    else
    {
        afficher_ecran(650, 300, resp[1], screen, NULL);
        Mix_PlayChannel(-1, respmus[1], 0);
    }
    SDL_Flip(screen);
    SDL_Delay(2000);
    Mix_FreeChunk(respmus[0]);
    Mix_FreeChunk(respmus[1]);
    SDL_FreeSurface(resp[0]);
    SDL_FreeSurface(resp[1]);
    SDL_FreeSurface(remaintime);
}

int init_enigme(enigme *e, char nomfich[], SDL_Surface *screen)
{
    e->rand = rand() % 3 + 1;
    SDL_Color white = {255, 255, 255};
    e->font = TTF_OpenFont("fonts/Retro.ttf", 18);
    FILE *F;
    char q[50], r[4][50];
    int i, j;
    F = fopen(nomfich, "r+");
    for (i = 0; i < e->rand; i++)
        fgets(q, 50, F);
    char **tokens;
    int count;
    count = split(q, ':', &tokens);

    e->RSurf = IMG_Load("images/Rectangle.png");
    e->Q = TTF_RenderText_Solid(e->font, tokens[0], white);
    e->R[0] = TTF_RenderText_Solid(e->font, tokens[1], white);
    e->R[1] = TTF_RenderText_Solid(e->font, tokens[2], white);
    e->R[2] = TTF_RenderText_Solid(e->font, tokens[3], white);
    e->RJ = atoi(tokens[4]);
    e->QM = IMG_Load("images/question_surface.png");
    for (i = 0; i < count; i++)
        free(tokens[i]);
    free(tokens);
    fclose(F);

    afficher_enigme(e, screen);
    SDL_Flip(screen);
    animer(e, screen);

    SDL_FreeSurface(e->QM);
    SDL_FreeSurface(e->Q);
    SDL_FreeSurface(e->R[0]);
    SDL_FreeSurface(e->R[1]);
    SDL_FreeSurface(e->R[2]);
    return 0;
}