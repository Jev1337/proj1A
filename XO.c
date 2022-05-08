#include "XO.h"
#include "gamehead.h"

void initialiserTic(tic *t)
{
    int i = 0;
    t->tic_background = IMG_Load("images/jeu.jpg");
    t->tic_X = IMG_Load("images/X.png");
    t->tic_O = IMG_Load("images/O.png");
    for (i = 0; i < 9; i++)
    {
        t->tabsuiv[i] = 0;
    }
    t->joueur = -1;
    t->tour = 0;
    t->font = TTF_OpenFont("fonts/comic.ttf", 100);
    if (t->font == NULL)
    {
        return;
    }
    t->color.b = 0;
    t->color.r = 0;
    t->color.g = 0;
    t->pos_premier.x = 0;
    t->pos_premier.y = 0;
    t->pos_text.x = 0;
    t->pos_text.x = 0;
}
void afficherTic(int tabsuivi[], SDL_Surface *ecran)
{
    SDL_Surface *gameBoard;
    SDL_Surface *playerX;
    SDL_Surface *playerO;

    int i, w = 0, h = 0;

    gameBoard = IMG_Load("images/jeu.bmp");
    playerO = IMG_Load("images/O.bmp");
    playerX = IMG_Load("images/X.bmp");
    afficher_ecran(0, 0, gameBoard, ecran,NULL);

    for (i = 0; i < 9; i++)
    {
        switch (tabsuivi[i])
        {
        case 1:
            afficher_ecran(w, h, playerO, ecran,NULL);

            break;
        case -1:
            afficher_ecran(w, h, playerX, ecran,NULL);
            break;
        }
        w += 200;
        if (w >= 600)
        {
            w = 0;
            h += 200;
        }
    }
    SDL_Flip(ecran);
}

int atilganer(int tabsuivi[])
{
    if ((tabsuivi[0] == 1 && tabsuivi[1] == 1 && tabsuivi[2] == 1) ||
        (tabsuivi[3] == 1 && tabsuivi[4] == 1 && tabsuivi[5] == 1) ||
        (tabsuivi[6] == 1 && tabsuivi[7] == 1 && tabsuivi[8] == 1) ||
        (tabsuivi[0] == 1 && tabsuivi[3] == 1 && tabsuivi[6] == 1) ||
        (tabsuivi[1] == 1 && tabsuivi[4] == 1 && tabsuivi[7] == 1) ||
        (tabsuivi[2] == 1 && tabsuivi[5] == 1 && tabsuivi[8] == 1) ||
        (tabsuivi[0] == 1 && tabsuivi[4] == 1 && tabsuivi[8] == 1) ||
        (tabsuivi[2] == 1 && tabsuivi[4] == 1 && tabsuivi[6] == 1))
        return 1;
    else if ((tabsuivi[0] == -1 && tabsuivi[1] == -1 && tabsuivi[2] == -1) ||
             (tabsuivi[3] == -1 && tabsuivi[4] == -1 && tabsuivi[5] == -1) ||
             (tabsuivi[6] == -1 && tabsuivi[7] == -1 && tabsuivi[8] == -1) ||
             (tabsuivi[0] == -1 && tabsuivi[3] == -1 && tabsuivi[6] == -1) ||
             (tabsuivi[1] == -1 && tabsuivi[4] == -1 && tabsuivi[7] == -1) ||
             (tabsuivi[2] == -1 && tabsuivi[5] == -1 && tabsuivi[8] == -1) ||
             (tabsuivi[0] == -1 && tabsuivi[4] == -1 && tabsuivi[8] == -1) ||
             (tabsuivi[2] == -1 && tabsuivi[4] == -1 && tabsuivi[6] == -1))
        return -1;
    else
        return 0;
}

void drawResult(SDL_Surface *screen, char string[], int x, int y, SDL_Color color, TTF_Font *font)
{
    SDL_Surface *textSurface;
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    textSurface = TTF_RenderText_Solid(font, string, color);
    if (textSurface == NULL)
    {
        return;
    }
    SDL_BlitSurface(textSurface, NULL, screen, &pos);
}
void Resultat(int tabsuivi[], SDL_Surface *ecran, tic t)
{
    if (atilganer(tabsuivi) == -1)
        drawResult(ecran, "Victoire", 0, 0, t.color, t.font);
    else if (atilganer(tabsuivi) == 1)
        drawResult(ecran, "Defaite", 0, 0, t.color, t.font);
    else
        drawResult(ecran, "NULLE", 0, 0, t.color, t.font);
    SDL_Flip(ecran);
    SDL_Delay(1000);
}
int minimax(int tabsuivi[9], int joueur)
{
    int gagnant = atilganer(tabsuivi);
    if (gagnant != 0)
        return gagnant * joueur;
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = joueur;
            int mmscore = -minimax(tabsuivi, joueur * -1);
            if (mmscore > score)
            {
                score = mmscore;
                coup = i;
            }
            tabsuivi[i] = 0;
        }
    }
    if (coup == -1)
        return 0;
    return score;
}
void calcul_coup(int tabsuivi[9])
{
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = 1;
            int mmscore = -minimax(tabsuivi, -1);
            tabsuivi[i] = 0;
            if (mmscore > score)
            {
                score = mmscore;
                coup = i;
            }
        }
    }
    tabsuivi[coup] = 1;
}