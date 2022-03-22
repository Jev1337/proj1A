#include "enigme.h"
#include "string.h"
int afficher_enigme(enigme *e, SDL_Surface *screen){
    int iscorrect;
    SDL_Event event;
    e->rand = rand() % 3 +1;
    init_enigme(e, "enigme.txt");
    afficher_ecran(700,250,e->QM, screen, NULL);
    afficher_ecran(500,800,e->RSurf,screen,NULL);
    afficher_ecran(600,840,e->R[0], screen, NULL);
    afficher_ecran(800,800,e->RSurf,screen,NULL);
    afficher_ecran(900,840,e->R[1], screen, NULL);
    afficher_ecran(1100,800,e->RSurf,screen,NULL);
    afficher_ecran(1200,840,e->R[2], screen, NULL);
    afficher_ecran(960,330,e->Q, screen, NULL);
    SDL_Flip(screen);
    iscorrect = animer(e, event);
    if (iscorrect)
    ;
        //score++
    else
        //score--
    ;
    return 0;
}


int animer(enigme *e, SDL_Event event){
    int resp = -1;
    int x,y;
    while (resp == -1){
            while (SDL_PollEvent(&event))
    {
    if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_1)
                resp=1;
            else if (event.key.keysym.sym == SDLK_2)
                resp=2;
            else if (event.key.keysym.sym == SDLK_3)
                resp=3;
        }
    if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (x >= 600 && x <= 269 + 600 && y >= 840 && y <= 840 + 119)
                {
                    resp = 1;
                }
                if (x >= 900 && x <= 269 + 900 && y >= 840 && y <= 840 + 119)
                {
                    resp = 2;
                }
                if (x >= 1200 && x <= 269 + 1200 && y >= 840 && y <= 840 + 119)
                {
                    resp = 3;
                }
            }
        }
    }
    }
    return resp == e->RJ;
}

int split (const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

void init_enigme(enigme *e, char nomfich[]){
    SDL_Color white = {255, 255, 255};
    e->font = TTF_OpenFont("fonts/Retro.ttf", 18);
    FILE* F;
    char q[50], r[4][50];
    int i,j;
    F= fopen(nomfich, "r+");
    for (i=0; i<e->rand; i++)
        fgets(q, 50, F);
    char **tokens;
    int count;
    count = split (q, ':', &tokens);
    e->RSurf= IMG_Load("images/Rectangle.png");
    e->Q = TTF_RenderText_Solid(e->font, tokens[0], white);
    e->R[0] = TTF_RenderText_Solid(e->font, tokens[1], white);
    e->R[1] = TTF_RenderText_Solid(e->font, tokens[2], white);
    e->R[2] = TTF_RenderText_Solid(e->font, tokens[3], white);
    e->RJ = atoi(tokens[4]);
    e->QM= IMG_Load("images/question_surface.png");
    for (i = 0; i < count; i++) free (tokens[i]);
        free (tokens);
    fclose(F);
}