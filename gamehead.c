
/**
 * @file gamehead.c
 * @author
 * Abdelmalek Amir Hassen
 * Yasmine Ayadi
 * Yassine Bouzouita
 * Mohamed Sghaier Chaaben
 * Nour Mbarki
 * Akkari Rihem
 * @brief This .c file includes the most important function that allows us to launch the game and manage the current screen
 * @version 0.7
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "en.h"
#include "XO.h"
#include "gamehead.h"

/**
 * @brief Afficher Menu is a function that starts the entire Video Game
 *
 * @param BD Button Dimentions are stored in here
 * @param B  Button SDL_Surfaces are stored in here
 * @param MI Menu Items are stored in here
 * @param GI Game Items are stored in here
 * @param SI Settings Items are stored in here
 * @param PI Pause Menu Items are stored in here
 * @param M Miscalenous items such as Sound are stored in here
 * @param p Character and it's specifications are stored in here
 * @param en Enemy specifications are stored in here
 * @param b Background and its characteristics are stored in here
 * @param screen The Screen SDL_Surface
 * @return 0 For quitting 1 For Exception Thrown
 */
int afficher_menu(btndim *BD, btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, character *popt, Ennemi *en, background *b, SDL_Surface *screen)
{
    show_menu(BD, GI, B, MI, SI, screen);
    enigme e;
    enigme2 e2;
    init_enigme2(&e2);
    int frame = 0;
    int cap = 1;
    Timer fps;
    int quit = 0;
    int actpos_previous = 1, actpos = 1;
    PickUp coin;
    initEnnemi(en);
    initCoin(&coin);
    minimap m;
    int run = 1, running = 1, alea;
    char image[30] = "";
    int t_prev, currentTime;
    SDL_Event event;
    tic t;
    int coup;
    int joueur;
    initialiserTic(&t);
    int a, bint;
    if (Mix_PlayMusic(M->music, -1) == -1)
    {
        return 1;
    }
    SDL_Surface *savemenu = IMG_Load("images/savemenu.png");

    initmap(&m, 0);
    init_bg(b, 0);
    initcharacter(p, 0);
    initcharacter(popt, 0);
    popt->offset.x = 1920/2;
    FILE *file = fopen("savegame.txt", "r");
    int c = fgetc(file);
    if (c == EOF)
        GI->LoadSave = 0;
    fclose(file);

    while (quit == 0)
    {
        start(&fps);
        if (actpos == 1) // If we are in the main menu
        {
            show_menu(BD, GI, B, MI, SI, screen);
            if (frame >= 8)
            {
                frame = 0;
            }

            afficher_ecran(0, 0, MI->rainspr, screen, &MI->rainclip[frame]);

            quit = menu(BD, B, GI, M, MI, SI, p, popt, b, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;

            if (actpos == 2 && GI->LoadSave)
            {
                /*afficher_ecran(700, 250, savemenu, screen, NULL);
                SDL_Flip(screen);
                GI->LoadSave = -1;
                while (GI->LoadSave == -1)
                    while (SDL_PollEvent(&event))
                    {

                        if (event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if (event.button.button == SDL_BUTTON_LEFT)
                            {
                                int x = event.button.x;
                                int y = event.button.y;
                                if (x >= 670 && x <= 269 + 670 && y >= 650 && y <= 650 + 119)
                                {
                                    GI->LoadSave = 1;
                                }
                                if (x >= 1080 && x <= 269 + 1080 && y >= 650 && y <= 650 + 119)
                                {
                                    GI->LoadSave = 0;
                                }
                            }
                        }
                    }
                */
                if (GI->LoadSave)
                {
                    charger(p, b, &m, GI);
                    printf("%d", GI->lvl);
                    switch (GI->lvl)
                    {
                    case 1:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Red(LevelOne).png");
                        b->imageM = IMG_Load("images/Red(LevelOne)Mask.png");
                        m.minimap = IMG_Load("images/Red(LevelOne)minimap.png");
                        GI->zoomable = IMG_Load("images/Red(LevelOne)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 2:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Red(LevelTwo).png");
                        b->imageM = IMG_Load("images/Red(LevelTwo)Mask.png");
                        m.minimap = IMG_Load("images/Red(LevelTwo)minimap.png");
                        GI->zoomable = IMG_Load("images/Red(LevelTwo)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 3:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Red(LevelThree).png");
                        b->imageM = IMG_Load("images/Red(LevelThree)Mask.png");
                        m.minimap = IMG_Load("images/Red(LevelThree)minimap.png");
                        GI->zoomable = IMG_Load("images/Red(LevelThree)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 4:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Red(LevelFour).png");
                        b->imageM = IMG_Load("images/Red(LevelFour)Mask.png");
                        m.minimap = IMG_Load("images/Red(LevelFour)minimap.png");
                        GI->zoomable = IMG_Load("images/Red(LevelFour)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 5:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Blue(LevelOne).png");
                        b->imageM = IMG_Load("images/Blue(LevelOne)Mask.png");
                        m.minimap = IMG_Load("images/Blue(LevelOne)minimap.png");
                        GI->zoomable = IMG_Load("images/Blue(LevelOne)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 6:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Blue(LevelTwo).png");
                        b->imageM = IMG_Load("images/Blue(LevelTwo)Mask.png");
                        m.minimap = IMG_Load("images/Blue(LevelTwo)minimap.png");
                        GI->zoomable = IMG_Load("images/Blue(LevelTwo)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 7:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Last(LevelOne).png");
                        b->imageM = IMG_Load("images/Last(LevelOne)Mask.png");
                        m.minimap = IMG_Load("images/Last(LevelOne)minimap.png");
                        GI->zoomable = IMG_Load("images/Last(LevelOne)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 8:
                        SDL_FreeSurface(b->image);
                        SDL_FreeSurface(m.minimap);
                        b->image = IMG_Load("images/Last(LevelTwo).png");
                        b->imageM = IMG_Load("images/Last(LevelTwo)Mask.png");
                        m.minimap = IMG_Load("images/Last(LevelTwo)minimap.png");
                        GI->zoomable = IMG_Load("images/Last(LevelTwo)minimapBIG.png");
                        show_game(BD, B, GI, b, screen);
                        SDL_Flip(screen);
                        break;
                    case 9:
                            GI->SecOpt = 0;
                            SDL_FreeSurface(b->image);
                            b->image = IMG_Load("images/Last(LevelThree).png");
                            b->imageM = IMG_Load("images/Last(LevelThree)Mask.png");
                            show_game(BD, B, GI, b, screen);
                            SDL_Flip(screen);
                        break;
                    }
                }
            }
            else if (GI->LoadSave == 0 && actpos == 2)
            {
                initmap(&m, 0);
                init_bg(b, 0);
                initcharacter(p, 0);
            }
        }
        if (actpos == 8)
        {
            afficherTic(t.tabsuiv, screen);
            printf("%d\n", atilganer(t.tabsuiv));
            if (t.tour < 9 && atilganer(t.tabsuiv) == 0)
            {
                if (t.joueur != -1)
                {
                    calcul_coup(t.tabsuiv);
                    t.joueur = -1;
                    t.tour++;
                }
                else
                {
                    SDL_WaitEvent(&event);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                    {

                        if (event.button.x > 0 && event.button.x <= 200 && event.button.y > 0 && event.button.y <= 200)
                            coup = 0;
                        if (event.button.x > 200 && event.button.x <= 400 && event.button.y > 0 && event.button.y <= 200)
                            coup = 1;
                        if (event.button.x > 400 && event.button.x <= 600 && event.button.y > 0 && event.button.y <= 200)
                            coup = 2;

                        if (event.button.x > 0 && event.button.x <= 200 && event.button.y > 200 && event.button.y <= 400)
                            coup = 3;
                        if (event.button.x > 200 && event.button.x <= 400 && event.button.y > 200 && event.button.y <= 400)
                            coup = 4;
                        if (event.button.x > 400 && event.button.x <= 600 && event.button.y > 200 && event.button.y <= 400)
                            coup = 5;

                        if (event.button.x > 0 && event.button.x <= 200 && event.button.y > 400 && event.button.y <= 600)
                            coup = 6;
                        if (event.button.x > 200 && event.button.x <= 400 && event.button.y > 400 && event.button.y <= 600)
                            coup = 7;
                        if (event.button.x > 400 && event.button.x <= 600 && event.button.y > 400 && event.button.y <= 600)
                            coup = 8;

                        t.tabsuiv[coup] = -1;
                        t.joueur = 1;
                        t.tour++;
                    }
                    else if (event.type == SDL_QUIT)
                    {
                        quit = 0;
                    }
                }
            }
            else
            {
                actpos = 2;
                Resultat(t.tabsuiv, screen, t);
                quit = 0;
            }
        }
        if (actpos == 4)
        {
            quit = setting(BD, B, PI, MI, GI, SI, M, b, &actpos, actpos_previous, screen);
            if (quit == 2)
                return 1;
        }
        if (actpos == 2)
        { // State of Game
            if (p->health == 0)
            {
                GI->lvl = 1;
                initmap(&m, 0);
                init_bg(b, 0);
                initcharacter(p, 0);
            }
            quit = game(BD, B, MI, GI, PI, M, p, popt, en, &coin, b, &m, &actpos, screen);
            if (quit == 2)
                return 1;
                }
        if (actpos == 5)
        {
            quit = pause(BD, B, SI, GI, PI, MI, M, b, &actpos, &actpos_previous, screen);
            if (quit == 2)
                return 1;
            if (actpos == 1)
            {
                sauvegarder(*p, *b, m, *GI);
                GI->LoadSave = 1;

                B->isselected[0] = 0;
                B->isselected[1] = 0;
                B->isselected[2] = 0;
                B->isselected[3] = 0;
                B->isselected[4] = 0;

            }
        }
        if (actpos == 6)
        {
            int result = init_enigme(&e, "enigme.txt", screen);
            if (!result)
                p->health--;
            actpos = 2;
        }
        if (actpos == 7)
        {
            int character_choice = 0, console_choice = 0;
            do
            {
                character2(screen, &character_choice);
            } while (character_choice == 0);
            printf("Your character choice is %d", character_choice);
            do
            {
                controller(screen, &console_choice);
            } while (console_choice == 0);
            printf("Your console choice is %d", console_choice);
            t_prev = SDL_GetTicks();
            generate_afficher(screen, image, &e2, &alea);
            running = 1;
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 0;
                break;
            }
            do
            {
                currentTime = (SDL_GetTicks() - t_prev) / 1000;

                SDL_BlitSurface(e2.img, NULL, screen, &(e2.p));
                SDL_BlitSurface(e2.animation.SpriteSheet, &e2.animation.Clips[e2.animation.ClipLoaded], screen, &e2.animation.pos);
                SDL_Delay(16);
                SDL_Flip(screen);
                if (currentTime <= 10)
                    e2.animation.ClipLoaded = 0;
                if (currentTime == 10)
                    e2.animation.ClipLoaded = 1;
                if (currentTime == 15)
                    e2.animation.ClipLoaded = 2;
                if (currentTime == 25)
                    e2.animation.ClipLoaded = 3;
                if (currentTime == 30)
                    e2.animation.ClipLoaded = 4;
                e2.reponse = resolution(&running, &run);
            } while (currentTime <= 30 && (e2.reponse > 3 || e2.reponse < 1) && running != 0);
            if (e2.reponse_juste == e2.reponse)
                afficher_resultat(screen, 1, &e2);
            else if (currentTime >= 30 && e2.reponse == 0)
            {
                afficher_resultat(screen, 0, &e2);
            }
            else
                afficher_resultat(screen, 0, &e2);
            SDL_Delay(16);
            SDL_Flip(screen);
            SDL_Delay(3000);
            actpos = 2;
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
    return 0;
}

/**
 * @brief FinProg is a function that frees Most of the loaded items especially from the menu
 *
 * @param B Button SDL_Surfaces to free
 * @param MI Menu Items to free
 * @param GI GameItems to free
 * @param SI SettingsItems to free
 * @param PI Pause Items to free
 * @param M Miscalenous Items to free
 * @param p Character items to free
 * @param screen Screen that we will free
 */
void finprog(btn *B, menuitems *MI, gameitems *GI, settingsitems *SI, pauseitems *PI, misc *M, character *p, character *popt, SDL_Surface *screen)
{

    Mix_FreeChunk(M->scratch);
    SDL_FreeSurface(MI->background);
    SDL_FreeSurface(SI->settings);
    SDL_FreeSurface(B->menubtns_u[0]);
    SDL_FreeSurface(B->menubtns_u[1]);
    SDL_FreeSurface(B->menubtns_u[2]);
    SDL_FreeSurface(B->menubtns_u[3]);
    SDL_FreeSurface(B->menubtns_u[4]);
    SDL_FreeSurface(B->menubtns_s[0]);
    SDL_FreeSurface(B->menubtns_s[1]);
    SDL_FreeSurface(B->menubtns_s[2]);
    SDL_FreeSurface(B->menubtns_s[3]);
    SDL_FreeSurface(B->menubtns_s[4]);
    SDL_FreeSurface(B->donebtn[0]);
    SDL_FreeSurface(B->donebtn[1]);
    SDL_FreeSurface(B->fsbtn[0]);
    SDL_FreeSurface(B->fsbtn[1]);
    SDL_FreeSurface(B->fsbtn[2]);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(PI->pausemenu);
    SDL_FreeSurface(MI->btnreset);
    SDL_FreeSurface(MI->rainspr);
    SDL_FreeSurface(MI->gamename);
    SDL_FreeSurface(MI->rightarrow);
    SDL_FreeSurface(MI->leftarrow);
    // Quit SDL
    SDL_Quit();
}
