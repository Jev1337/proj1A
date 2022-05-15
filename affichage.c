#include "gamehead.h"

int menu(btndim *BD, btn *B, gameitems *GI, misc *M, menuitems *MI, settingsitems *SI, character *p, character *popt, background *b, int *actpos, int *actpos_previous, SDL_Surface *screen)
{
    SDL_Event event;
    int x, y, i;

    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            for (i = 0; i < 5; i++)
            {
                if (x >= BD->menubtns[i].x && x <= BD->menubtns[i].w + BD->menubtns[i].x && y >= BD->menubtns[i].y && y <= BD->menubtns[i].y + BD->menubtns[i].h)
                {
                    if (B->isselected[i] == 0)
                    {
                        B->isselected[i] = 1;
                    }
                }
                else
                {
                    if (B->isselected[i] == 1)
                    {
                        B->isselected[i] = 0;
                    }
                }
            }
        }

        if (event.type == SDL_QUIT)
            return 1;
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (B->isselected[4] == 2) // NewGame
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 2;
                    Mix_HaltMusic();
                    show_game(BD, B, GI, b, screen);
                    GI->LoadSave = 0;
                    B->isselected[4] = 0;
                }
                if (B->isselected[0] == 2 && GI->LoadSave == 1) // Continue
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 2;
                    Mix_HaltMusic();
                    show_game(BD, B, GI, b, screen);
                    GI->LoadSave = 1;
                    B->isselected[0] = 0;
                }
                /*if (B->isselected[1]) // Credits
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos = 3;
                    show_credits(BD, B, MI, SI, screen);
                }*/
                if (B->isselected[3] == 2) // Settings
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 4;
                    show_settings(BD, B, SI, M, screen);
                    B->isselected[3] = 0;
                }
                if (B->isselected[2] == 2) // Quit
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    return 1;
                    B->isselected[2] = 0;
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (B->isselected[4]) // NewGame
                {
                    // afficher_ecran(BD->menubtns[4].x, BD->menubtns[4].y, B->menubtns_ss[4], screen, NULL);
                    B->isselected[4] = 2;
                }
                if (B->isselected[0]) // Continue
                {
                    // afficher_ecran(BD->menubtns[0].x, BD->menubtns[0].y, B->menubtns_ss[0], screen, NULL);
                    B->isselected[0] = 2;
                }

                if (B->isselected[3]) // Settings
                {
                    // afficher_ecran(BD->menubtns[3].x, BD->menubtns[3].y, B->menubtns_ss[3], screen, NULL);
                    B->isselected[3] = 2;
                }
                if (B->isselected[2]) // Quit
                {
                    // afficher_ecran(BD->menubtns[2].x, BD->menubtns[2].y, B->menubtns_ss[2], screen, NULL);
                    B->isselected[2] = 2;
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                if (B->isselected[0] == 0 && B->isselected[4] == 0 && B->isselected[3] == 0 && B->isselected[2] == 0)
                {
                    B->isselected[0] = 1;
                }
                else if (B->isselected[0])
                {
                    B->isselected[0] = 0;
                    B->isselected[4] = 1;
                }
                else if (B->isselected[4])
                {
                    B->isselected[4] = 0;
                    B->isselected[3] = 1;
                }
                else if (B->isselected[3])
                {
                    B->isselected[2] = 1;
                    B->isselected[3] = 0;
                }
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                if (B->isselected[0] == 0 && B->isselected[4] == 0 && B->isselected[3] == 0 && B->isselected[2] == 0)
                {
                    B->isselected[0] = 1;
                }
                else if (B->isselected[2])
                {
                    B->isselected[2] = 0;
                    B->isselected[3] = 1;
                }
                else if (B->isselected[3])
                {
                    B->isselected[3] = 0;
                    B->isselected[4] = 1;
                }
                else if (B->isselected[4])
                {
                    B->isselected[4] = 0;
                    B->isselected[0] = 1;
                }
            }
            if (event.key.keysym.sym == SDLK_RETURN)
            {

                if (B->isselected[0] == 1)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 2;
                    Mix_HaltMusic();
                    show_game(BD, B, GI, b, screen);
                    GI->LoadSave = 1;
                }
                else if (B->isselected[4])
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 2;
                    Mix_HaltMusic();
                    show_game(BD, B, GI, b, screen);
                    GI->LoadSave = 0;
                }
                else if (B->isselected[3])
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 4;
                    show_settings(BD, B, SI, M, screen);
                }

                else if (B->isselected[2])
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    return 1;
                }
            }
            if (event.key.keysym.sym == SDLK_g)
            {
                // If there is no music playing
                if (Mix_PlayingMusic() == 0)
                {
                    // Play the music
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 2;
                    }
                }
                // If music is being played
                else
                {
                    // If the music is paused
                    if (Mix_PausedMusic() == 1)
                    {
                        // Resume the music
                        Mix_ResumeMusic();
                    }
                    // If the music is playing
                    else
                    {
                        // Pause the music
                        Mix_PauseMusic();
                    }
                }
            }
            else if (event.key.keysym.sym == SDLK_x)
            {
                // Stop the music
                Mix_HaltMusic();
            }
        }
    }

    return 0;
}

int setting(btndim *BD, btn *B, pauseitems *PI, menuitems *MI, gameitems *GI, settingsitems *SI, misc *M, background *b, int *actpos, int actpos_previous, SDL_Surface *screen)
{
    SDL_Event event;
    int x, y;
    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= BD->donebtn.x && x <= BD->donebtn.w + BD->donebtn.x && y >= BD->donebtn.y && y <= BD->donebtn.y + BD->donebtn.h)
            {

                if (B->isselected[5] == 0)
                {
                    B->isselected[5] = 1;
                    afficher_ecran(BD->donebtn.x, BD->donebtn.y, B->donebtn[1], screen, NULL);
                }
            }
            else
            {
                if (B->isselected[5] == 1)
                {
                    B->isselected[5] = 0;
                    show_settings(BD, B, SI, M, screen);
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (x >= BD->donebtn.x && x <= BD->donebtn.w + BD->donebtn.x && y >= BD->donebtn.y && y <= BD->donebtn.y + BD->donebtn.h)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    if (actpos_previous == 1)
                        show_menu(BD,GI, B, MI, SI, screen);
                    if (actpos_previous == 5)
                        show_pausemenu(BD, B, MI, GI, PI, b, screen);
                    *actpos = actpos_previous;
                    // applysettings
                }
                if (x >= 1227 && x <= 1263 && y >= 390 && y <= 436)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volumeSFX = 19;
                    show_settings(BD, B, SI, M, screen);
                    Mix_VolumeMusic(M->volumeSFX);

                    // applysettings
                }
                if (x >= 1269 && x <= 1306 && y >= 390 && y <= 436)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volumeSFX = 35;
                    Mix_VolumeMusic(M->volumeSFX);

                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1313 && x <= 1349 && y >= 390 && y <= 436)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volumeSFX = 51;

                    Mix_VolumeMusic(M->volumeSFX);

                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1353 && x <= 1391 && y >= 390 && y <= 436)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volumeSFX = 67;
                    Mix_VolumeMusic(M->volumeSFX);

                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1395 && x <= 1433 && y >= 390 && y <= 436)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volumeSFX = 83;
                    Mix_VolumeMusic(M->volumeSFX);

                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1437 && x <= 1475 && y >= 390 && y <= 436)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volumeSFX = 128;
                    Mix_VolumeMusic(M->volumeSFX);

                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }

                //----

                if (x >= 1227 && x <= 1263 && y >= 524 && y <= 570)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 19;
                    show_settings(BD, B, SI, M, screen);

                    Mix_Volume(1, M->volume);

                    // applysettings
                }
                if (x >= 1269 && x <= 1306 && y >= 524 && y <= 570)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 35;

                    Mix_Volume(1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1313 && x <= 1349 && y >= 524 && y <= 570)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 51;

                    Mix_Volume(1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1353 && x <= 1391 && y >= 524 && y <= 570)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 67;

                    Mix_Volume(1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1395 && x <= 1433 && y >= 524 && y <= 570)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 83;

                    Mix_Volume(1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1437 && x <= 1475 && y >= 524 && y <= 570)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 128;

                    Mix_Volume(1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                // 1479 1517
                if (x >= 1587 && x <= 1633 && y >= 716 && y <= 768 && B->isselected[7] != 2)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    if (B->isselected[7] == 0)
                    {
                        B->isselected[7] = 1;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);
                        if (actpos_previous == 1)
                            show_menu(BD,GI, B, MI, SI, screen);
                        if (actpos_previous == 5)
                            show_pausemenu(BD, B, MI, GI, PI, b, screen);
                        show_settings(BD, B, SI, M, screen);
                    }

                    else if (B->isselected[7] == 1)
                    {
                        B->isselected[7] = 2;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE | SDL_RESIZABLE);
                        if (actpos_previous == 1)
                            show_menu(BD,GI, B, MI, SI, screen);
                        if (actpos_previous == 5)
                            show_pausemenu(BD, B, MI, GI, PI, b, screen);
                        show_settings(BD, B, SI, M, screen);
                    }
                }
                if (x >= 1216 && x <= 1262 && y >= 714 && y <= 766 && B->isselected[7] != 0)
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    if (B->isselected[7] == 2)
                    {
                        B->isselected[7] = 1;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);
                        if (actpos_previous == 1)
                            show_menu(BD,GI, B, MI, SI, screen);
                        if (actpos_previous == 5)
                            show_pausemenu(BD, B, MI, GI, PI, b, screen);
                        show_settings(BD, B, SI, M, screen);
                    }
                    else if (B->isselected[7] == 1)
                    {
                        B->isselected[7] = 0;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE | SDL_FULLSCREEN);
                        if (actpos_previous == 1)
                            show_menu(BD,GI, B, MI, SI, screen);
                        if (actpos_previous == 5)
                            show_pausemenu(BD, B, MI, GI, PI, b, screen);
                        show_settings(BD, B, SI, M, screen);
                    }
                }
            }
        }
        if (event.type == SDL_VIDEORESIZE)
        {
            // Resize
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_j)
            {
                if (actpos_previous == 1)
                    show_menu(BD,GI, B, MI, SI, screen);
                if (actpos_previous == 2)
                {
                    // load game progress
                    show_game(BD, B, GI, b, screen);
                }
                *actpos = actpos_previous;
            }
            if (actpos_previous == 1)
            {
                if (event.key.keysym.sym == SDLK_g)
                {
                    // If there is no music playing
                    if (Mix_PlayingMusic() == 0)
                    {
                        // Play the music
                        if (Mix_PlayMusic(M->music, -1) == -1)
                        {
                            return 2;
                        }
                    }
                    // If music is being played
                    else
                    {
                        // If the music is paused
                        if (Mix_PausedMusic() == 1)
                        {
                            // Resume the music
                            Mix_ResumeMusic();
                        }
                        // If the music is playing
                        else
                        {
                            // Pause the music
                            Mix_PauseMusic();
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_x)
                {
                    // Stop the music
                    Mix_HaltMusic();
                }
            }
        }
        if (event.type == SDL_QUIT)
            return 1;
    }
    return 0;
}

int game(btndim *BD, btn *B, menuitems *MI, gameitems *GI, pauseitems *PI, misc *M, character *p, character *popt, Ennemi *e, PickUp *coin, background *b, minimap *m, int *actpos, SDL_Surface *screen)
{
    SDL_Event event;
    show_game(BD, B, GI, b, screen);
    afficher_character(p, screen);
    afficher_ecran(0, 50, GI->heart, screen, &GI->heartClip[abs(p->health - 5)]);
    if (GI->lvl != 9)
        afficherminimap(*m, GI->zoomable, screen);
    affichertemps(time(NULL) - m->temps, screen);

    if (GI->SecOpt)
        afficher_character(popt, screen);
    if (GI->lvl == 9)
    {
        if (e->attack)
        {
            afficherAttack(*e, screen);
            attackPerso(e, screen);
        }
        else
            afficherEnnemi(*e, screen);
        animerCoin(coin);
        deplacerIA(e, p->offset);
        afficher_ecran(1300, 800, coin->animation.spriteSheet[0], screen, &coin->animation.Clips[coin->animation.clipLoaded]); // afficher coin
    }
    if (GI->lvl == 9)
        if (collisionBB(p->offset, e->pos) == 1)
        {
            p->offset.x = 0;
            p->health--;
        }

    if (collisionBB(p->offset, coin->pos) == 1)
    {
        *actpos = 1;
        printf("\nScore = 3921\n");
    }

    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ((b->posmask.x >= 6780) && GI->lvl != 9)
    {
        m->pospoint.x = 400;
        m->pospoint.y = 80;
        *actpos = 6;
        GI->lvl++;
        b->posmask.x = 0;
        p->offset.x = 0;
        b->posimage.x = 0;
        switch (GI->lvl)
        {
        case 1:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Red(LevelOne).png");
            b->imageM = IMG_Load("images/Red(LevelOne)Mask.png");
            m->minimap = IMG_Load("images/Red(LevelOne)minimap.png");
            GI->zoomable = IMG_Load("images/Red(LevelOne)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 2:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Red(LevelTwo).png");
            b->imageM = IMG_Load("images/Red(LevelTwo)Mask.png");
            m->minimap = IMG_Load("images/Red(LevelTwo)minimap.png");
            GI->zoomable = IMG_Load("images/Red(LevelTwo)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 3:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Red(LevelThree).png");
            b->imageM = IMG_Load("images/Red(LevelThree)Mask.png");
            m->minimap = IMG_Load("images/Red(LevelThree)minimap.png");
            GI->zoomable = IMG_Load("images/Red(LevelThree)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 4:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Red(LevelFour).png");
            b->imageM = IMG_Load("images/Red(LevelFour)Mask.png");
            m->minimap = IMG_Load("images/Red(LevelFour)minimap.png");
            GI->zoomable = IMG_Load("images/Red(LevelFour)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 5:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Blue(LevelOne).png");
            b->imageM = IMG_Load("images/Blue(LevelOne)Mask.png");
            m->minimap = IMG_Load("images/Blue(LevelOne)minimap.png");
            GI->zoomable = IMG_Load("images/Blue(LevelOne)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 6:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Blue(LevelTwo).png");
            b->imageM = IMG_Load("images/Blue(LevelTwo)Mask.png");
            m->minimap = IMG_Load("images/Blue(LevelTwo)minimap.png");
            GI->zoomable = IMG_Load("images/Blue(LevelTwo)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 7:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Last(LevelOne).png");
            b->imageM = IMG_Load("images/Last(LevelOne)Mask.png");
            m->minimap = IMG_Load("images/Last(LevelOne)minimap.png");
            GI->zoomable = IMG_Load("images/Last(LevelOne)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 8:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            SDL_FreeSurface(m->minimap);
            b->image = IMG_Load("images/Last(LevelTwo).png");
            b->imageM = IMG_Load("images/Last(LevelTwo)Mask.png");
            m->minimap = IMG_Load("images/Last(LevelTwo)minimap.png");
            GI->zoomable = IMG_Load("images/Last(LevelTwo)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 9:
            GI->SecOpt = 0;
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image);
            b->image = IMG_Load("images/Last(LevelThree).png");
            b->imageM = IMG_Load("images/Last(LevelThree)Mask.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        }
    }

    //----------
    if (GI->SecOpt)
    if ((b->posmask2.x >= 6890) && MI->lvl != 9)
    {
        //m->pospoint.x = 400;
        //m->pospoint.y = 80;
        *actpos = 6;
        MI->lvl++;
        b->posmask2.x = 0;
        popt->offset.x = 1920/2;
        b->posimage2.x = 0;
        switch (MI->lvl)
        {
        case 1:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Red(LevelOne).png");
            b->imageM2 = IMG_Load("images/Red(LevelOne)Mask.png");
            //m->minimap = IMG_Load("images/Red(LevelOne)minimap.png");
            //GI->zoomable = IMG_Load("images/Red(LevelOne)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 2:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Red(LevelTwo).png");
            b->imageM2 = IMG_Load("images/Red(LevelTwo)Mask.png");
            //m->minimap = IMG_Load("images/Red(LevelTwo)minimap.png");
            //GI->zoomable = IMG_Load("images/Red(LevelTwo)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 3:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Red(LevelThree).png");
            b->imageM2 = IMG_Load("images/Red(LevelThree)Mask.png");
            //m->minimap = IMG_Load("images/Red(LevelThree)minimap.png");
            //GI->zoomable = IMG_Load("images/Red(LevelThree)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 4:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Red(LevelFour).png");
            b->imageM2 = IMG_Load("images/Red(LevelFour)Mask.png");
            //m->minimap = IMG_Load("images/Red(LevelFour)minimap.png");
            //GI->zoomable = IMG_Load("images/Red(LevelFour)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 5:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
           // SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Blue(LevelOne).png");
            b->imageM2 = IMG_Load("images/Blue(LevelOne)Mask.png");
            //m->minimap = IMG_Load("images/Blue(LevelOne)minimap.png");
            //GI->zoomable = IMG_Load("images/Blue(LevelOne)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 6:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Blue(LevelTwo).png");
            b->imageM2 = IMG_Load("images/Blue(LevelTwo)Mask.png");
            //m->minimap = IMG_Load("images/Blue(LevelTwo)minimap.png");
            //GI->zoomable = IMG_Load("images/Blue(LevelTwo)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 7:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Last(LevelOne).png");
            b->imageM2 = IMG_Load("images/Last(LevelOne)Mask.png");
            //m->minimap = IMG_Load("images/Last(LevelOne)minimap.png");
            //GI->zoomable = IMG_Load("images/Last(LevelOne)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 8:
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            //SDL_FreeSurface(m->minimap);
            b->image2 = IMG_Load("images/Last(LevelTwo).png");
            b->imageM2 = IMG_Load("images/Last(LevelTwo)Mask.png");
            //m->minimap = IMG_Load("images/Last(LevelTwo)minimap.png");
            //GI->zoomable = IMG_Load("images/Last(LevelTwo)minimapBIG.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        case 9:
            GI->lvl = 9;
            GI->SecOpt = 0;
            SDL_FillRect(screen, NULL, 0xB2B2B2);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x5C5C5C);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0x222222);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FillRect(screen, NULL, 0);
            SDL_Delay(100);
            SDL_Flip(screen);
            SDL_FreeSurface(b->image2);
            SDL_FreeSurface(b->image);
            b->image = IMG_Load("images/Last(LevelThree).png");
            b->imageM = IMG_Load("images/Last(LevelThree)Mask.png");
            show_game(BD, B, GI, b, screen);
            SDL_Flip(screen);
            break;
        }
    }

    if (keystate[SDLK_ESCAPE])
    {
        *actpos = 5;
        show_pausemenu(BD, B, MI, GI, PI, b, screen);
    }
    if (keystate[SDLK_p])
    {
        *actpos = 8;
    }
    if (keystate[SDLK_l])
    {
        *actpos = 7;
    }
    if (keystate[SDLK_UP])
    {
        jump(p, popt, 1, BD, B, GI, e, *coin, b, m, screen);
    }
    if (GI->SecOpt)
        if (keystate[SDLK_w])
        {
            jump(p, popt, 2, BD, B, GI, e, *coin, b, m, screen);
        }

    SDL_PollEvent(&event);

    setcharacter(p, popt, keystate);

    changedirection(p, popt, m, b, GI, GI->SecOpt);

    return 0;
}

int pause(btndim *BD, btn *B, settingsitems *SI, gameitems *GI, pauseitems *PI, menuitems *MI, misc *M, background *b, int *actpos, int *actpos_previous, SDL_Surface *screen)
{
    SDL_Event event;
    int x, y;
    while (SDL_PollEvent(&event))
    {
        /*if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            *actpos = 2;
            show_game(BD, B, GI, screen);
        }
        */
        // Temporarily Disabled
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (x >= 760 && x <= 1159 && y >= 665 && y <= 784) // quit
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    if (Mix_PlayMusic(M->music, -1) == -1)
                    {
                        return 1;
                    }
                    *actpos_previous = 1;
                    *actpos = 1;

                }
                if (x >= 760 && x <= 1159 && y >= 413 && y <= 532) // resume
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    // load the game with the save
                    show_game(BD, B, GI, b, screen);

                    *actpos = 2;
                }
                if (x >= 760 && x <= 1159 && y >= 540 && y <= 659) // settings
                {
                    if (Mix_PlayChannel(1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 5;
                    *actpos = 4;
                    show_settings(BD, B, SI, M, screen);
                }
            }
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= 760 && x <= 1159 && y >= 665 && y <= 784)
            {

                if (B->isselected[2] == 0)
                {
                    B->isselected[2] = 1;
                    afficher_ecran(720, 700, B->menubtns_s[2], screen, NULL);
                }
            }
            else
            {
                if (B->isselected[2] == 1)
                {
                    B->isselected[2] = 0;
                    show_pausemenu(BD, B, MI, GI, PI, b, screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 413 && y <= 532)
            {

                if (B->isselected[5] == 0)
                {
                    B->isselected[5] = 1;
                    afficher_ecran(720, 400, B->menubtns_s[0], screen, NULL);
                }
            }
            else
            {
                if (B->isselected[5] == 1)
                {
                    B->isselected[5] = 0;
                    show_pausemenu(BD, B, MI, GI, PI, b, screen);
                }
            }

            if (x >= 760 && x <= 1159 && y >= 540 && y <= 659)
            {

                if (B->isselected[6] == 0)
                {
                    B->isselected[6] = 1;
                    afficher_ecran(720,550, B->menubtns_s[3], screen, NULL);
                }
            }
            else
            {
                if (B->isselected[6] == 1)
                {
                    B->isselected[6] = 0;
                    show_pausemenu(BD, B, MI, GI, PI, b, screen);
                }
            }
        }
    }
    if (event.type == SDL_QUIT)
        return 1;
    return 0;
}

void show_menu(btndim *BD, gameitems *GI, btn *B, menuitems *MI, settingsitems *SI, SDL_Surface *screen)
{
    afficher_ecran(0, 0, MI->background, screen, NULL);
    /*afficher_ecran(896.01, 305.14, MI->gamename, screen, NULL);*/
    if (GI->LoadSave)
        afficher_ecran(0, 299, MI->btnreset, screen, NULL);
    else
        afficher_ecran(0, 299, B->menubtns_ss[1], screen, NULL);
    if (B->isselected[0] == 1 && GI->LoadSave == 1)
    {
        afficher_ecran(BD->menubtns[0].x, BD->menubtns[0].y, B->menubtns_s[0], screen, NULL);
        /*afficher_ecran(684, 534, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 534, MI->rightarrow, screen, NULL);*/
    }

    if (B->isselected[1] == 1)
    {
        /*afficher_ecran(BD->menubtns[1].x, BD->menubtns[1].y, B->menubtns_s[1], screen, NULL);
        afficher_ecran(684, 680, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 680, MI->rightarrow, screen, NULL);*/
    }
    if (B->isselected[2] == 1)
    {

        afficher_ecran(BD->menubtns[2].x, BD->menubtns[2].y, B->menubtns_s[2], screen, NULL);
        /*afficher_ecran(684, 814, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 814, MI->rightarrow, screen, NULL);*/
    }
   
    if (B->isselected[3] == 1 )
    {
        afficher_ecran(BD->menubtns[3].x, BD->menubtns[3].y, B->menubtns_s[3], screen, NULL);
    }
    if (B->isselected[4] == 1)
    {
        afficher_ecran(BD->menubtns[4].x, BD->menubtns[4].y, B->menubtns_s[4], screen, NULL);
    }
        

    if (B->isselected[0] == 2 && GI->LoadSave == 1)
    {
        afficher_ecran(BD->menubtns[0].x, BD->menubtns[0].y, B->menubtns_ss[0], screen, NULL);
        /*afficher_ecran(684, 534, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 534, MI->rightarrow, screen, NULL);*/
    }
    if (B->isselected[1] == 2)
    {
        afficher_ecran(BD->menubtns[1].x, BD->menubtns[1].y, B->menubtns_ss[1], screen, NULL);
        /*afficher_ecran(BD->menubtns[1].x, BD->menubtns[1].y, B->menubtns_s[1], screen, NULL);
        afficher_ecran(684, 680, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 680, MI->rightarrow, screen, NULL);*/
    }
    if (B->isselected[2] == 2)
    {

        afficher_ecran(BD->menubtns[2].x, BD->menubtns[2].y, B->menubtns_ss[2], screen, NULL);
        /*afficher_ecran(684, 814, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 814, MI->rightarrow, screen, NULL);*/
    }
    if (B->isselected[3] == 2)
    {
        afficher_ecran(BD->menubtns[3].x, BD->menubtns[3].y, B->menubtns_ss[3], screen, NULL);
    }
    if (B->isselected[4] == 2)
    {
        afficher_ecran(BD->menubtns[4].x, BD->menubtns[4].y, B->menubtns_ss[4], screen, NULL);
    }
}

void show_pausemenu(btndim *BD, btn *B, menuitems *MI, gameitems *GI, pauseitems *PI, background *b, SDL_Surface *screen)
{
    show_game(BD, B, GI, b, screen);
    afficher_ecran(0, 0, PI->pausemenu, screen, NULL);
    afficher_ecran(720, 400, B->menubtns_u[0], screen, NULL);
    afficher_ecran(720, 550, B->menubtns_u[3], screen, NULL);
    afficher_ecran(720, 700, B->menubtns_u[2], screen, NULL);
}

void show_game(btndim *BD, btn *B, gameitems *GI, background *b, SDL_Surface *screen)
{
    /*if (GI->SecOpt){
        SDL_Rect clip1, clip2;
        clip1 = b->posmask;
        clip2= bopt->posmask;
        clip1.y=0;
        clip2.y=0;
        clip1.h = 1080;
        clip2.h = 1080;
        clip1.w = 1920/2;
        clip2.w = 1920/2;
        afficher_ecran(b->posimage.x, b->posimage.y, b->image, screen, NULL);
        afficher_ecran(bopt->posimage.x, bopt->posimage.y, bopt->image, screen, NULL);
    }
    else*/
    if (GI->SecOpt){
            afficher_ecran(0, 0, b->image, screen, &b->posimage);
            afficher_ecran(1920/2, 0, b->image2, screen, &b->posimage2);
    }else
        afficher_ecran(b->posimage.x, b->posimage.y, b->image, screen, NULL);
}

void show_settings(btndim *BD, btn *B, settingsitems *SI, misc *M, SDL_Surface *screen)
{
    afficher_ecran(0, 0, SI->settings, screen, NULL);
    if (B->isselected[7] == 0)
        afficher_ecran(1201, 612, B->fsbtn[0], screen, NULL);
    else if (B->isselected[7] == 1)
        afficher_ecran(1201, 612, B->fsbtn[2], screen, NULL);
    else 
        afficher_ecran(1201, 612, B->fsbtn[1], screen, NULL);
    // afficher_ecran(1222,520,SI->volume[0],screen, NULL);

    switch (M->volume)
    {
    case 128:
        afficher_ecran(1222, 520, SI->volume[5], screen, NULL);
        break;
    case 83:
        afficher_ecran(1222, 520, SI->volume[4], screen, NULL);
        break;
    case 67:
        afficher_ecran(1222, 520, SI->volume[3], screen, NULL);
        break;
    case 51:
        afficher_ecran(1222, 520, SI->volume[2], screen, NULL);
        break;
    case 35:
        afficher_ecran(1222, 520, SI->volume[1], screen, NULL);
        break;
    case 19:
        afficher_ecran(1222, 520, SI->volume[0], screen, NULL);
        break;
    }
    switch (M->volumeSFX)
    {
    case 128:
        afficher_ecran(1222, 385, SI->volume[5], screen, NULL);
        break;
    case 83:
        afficher_ecran(1222, 385, SI->volume[4], screen, NULL);
        break;
    case 67:
        afficher_ecran(1222, 385, SI->volume[3], screen, NULL);
        break;
    case 51:
        afficher_ecran(1222, 385, SI->volume[2], screen, NULL);
        break;
    case 35:
        afficher_ecran(1222, 385, SI->volume[1], screen, NULL);
        break;
    case 19:
        afficher_ecran(1222, 385, SI->volume[0], screen, NULL);
        break;
    }
}