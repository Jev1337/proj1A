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
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (B->isselected[4]) // Gitbutton
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    // actpos = 2;
                }
                if (B->isselected[0]) // Continue
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 2;
                    Mix_HaltMusic();
                    show_game(BD, B, GI, b,screen);
                }
                if (B->isselected[1]) // Credits
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos = 3;
                    show_credits(BD, B, MI, SI, screen);
                }
                if (B->isselected[3]) // Settings
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 4;
                    show_settings(BD, B, SI, M, screen);
                }
                if (B->isselected[2]) // Quit
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    return 1;
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                if (B->isselected[0] == 0 && B->isselected[1] == 0 && B->isselected[2] == 0)
                {
                    B->isselected[0] = 1;
                }
                else if (B->isselected[0] == 1)
                {
                    B->isselected[0] = 0;
                    B->isselected[1] = 1;
                }
                else if (B->isselected[1] == 1)
                {
                    B->isselected[1] = 0;
                    B->isselected[2] = 1;
                }
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                if (B->isselected[0] == 0 && B->isselected[1] == 0 && B->isselected[2] == 0)
                {
                    B->isselected[0] = 1;
                }
                else if (B->isselected[1] == 1)
                {
                    B->isselected[1] = 0;
                    B->isselected[0] = 1;
                }
                else if (B->isselected[2] == 1)
                {
                    B->isselected[2] = 0;
                    B->isselected[1] = 1;
                }
            }
            if (event.key.keysym.sym == SDLK_RETURN)
            {

                if (B->isselected[0] == 1)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos_previous = 1;
                    *actpos = 2;
                    show_game(BD, B, GI, b, screen);
                }

                else if (B->isselected[1] == 1)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    *actpos = 3;
                    show_credits(BD, B, MI, SI, screen);
                }

                else if (B->isselected[2] == 1)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
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

int credit(btndim *BD, btn *B, misc *M, menuitems *MI, settingsitems *SI, int *actpos, SDL_Surface *screen)
{
    SDL_Event event;
    int x, y;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
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
        if (event.type == SDL_MOUSEMOTION)
        {
            x = event.motion.x;
            y = event.motion.y;
            if (x >= BD->donebtn.x && x <= BD->donebtn.w + BD->donebtn.x && y >= BD->donebtn.y && y <= BD->donebtn.y + BD->donebtn.h)
            {

                if (B->isselected[5] == 0)
                {
                    B->isselected[5] = 1;
                    afficher_ecran(776, 779, B->donebtn[1], screen, NULL);
                }
            }
            else
            {
                if (B->isselected[5] == 1)
                {
                    B->isselected[5] = 0;
                    show_credits(BD, B, MI, SI, screen);
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            x = event.button.x;
            y = event.button.y;
            if (B->isselected[5])
            {
                if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                {
                    return 2;
                }
                show_menu(BD, B, MI, SI, screen);

                *actpos = 1;
                // applysettings
            }
        }
        if (event.type == SDL_QUIT)
            return 1;
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
                    afficher_ecran(776, 779, B->donebtn[1], screen, NULL);
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
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (x >= 775 && x <= 1166 && y >= 779 && y <= 890)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    if (actpos_previous == 1)
                        show_menu(BD, B, MI, SI, screen);
                    if (actpos_previous == 5)
                        show_pausemenu(BD, B, MI, GI, PI, b, screen);
                    *actpos = actpos_previous;
                    // applysettings
                }
                if (x >= 1108 && x <= 1121 && y >= 386 && y <= 477)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 19;
                    show_settings(BD, B, SI, M, screen);
                    Mix_VolumeMusic(M->volume);
                    Mix_Volume(-1, M->volume);

                    // applysettings
                }
                if (x >= 1128 && x <= 1141 && y >= 386 && y <= 477)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 35;
                    Mix_VolumeMusic(M->volume);
                    Mix_Volume(-1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1148 && x <= 1161 && y >= 386 && y <= 477)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 51;

                    Mix_VolumeMusic(M->volume);
                    Mix_Volume(-1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1168 && x <= 1181 && y >= 386 && y <= 477)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 67;
                    Mix_VolumeMusic(M->volume);
                    Mix_Volume(-1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1188 && x <= 1201 && y >= 386 && y <= 477)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 83;
                    Mix_VolumeMusic(M->volume);
                    Mix_Volume(-1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 1208 && x <= 1221 && y >= 386 && y <= 477)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    M->volume = 128;
                    Mix_VolumeMusic(M->volume);
                    Mix_Volume(-1, M->volume);
                    show_settings(BD, B, SI, M, screen);

                    // applysettings
                }
                if (x >= 775 && x <= 1166 && y >= 500 && y <= 611)
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    if (B->isselected[6] == 0)
                    {
                        B->isselected[6] = 1;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE);
                        if (actpos_previous == 1)
                            show_menu(BD, B, MI, SI, screen);
                        if (actpos_previous == 5)
                            show_pausemenu(BD, B, MI, GI, PI, b, screen);
                        show_settings(BD, B, SI, M, screen);
                        afficher_ecran(776, 500, B->fsbtn[2], screen, NULL);
                    }

                    else if (B->isselected[6] == 1)
                    {
                        B->isselected[6] = 2;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE | SDL_RESIZABLE);
                        if (actpos_previous == 1)
                            show_menu(BD, B, MI, SI, screen);
                        if (actpos_previous == 5)
                            show_pausemenu(BD, B, MI, GI, PI, b, screen);
                        show_settings(BD, B, SI, M, screen);
                        afficher_ecran(776, 500, B->fsbtn[1], screen, NULL);
                    }
                    else
                    {
                        B->isselected[6] = 0;
                        screen = SDL_SetVideoMode(M->SCREEN_W, M->SCREEN_H, SCREEN_BBP, SDL_SWSURFACE | SDL_FULLSCREEN);
                        if (actpos_previous == 1)
                            show_menu(BD, B, MI, SI, screen);
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
                    show_menu(BD, B, MI, SI, screen);
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
    afficherminimap(*m, GI->zoomable, screen);
    affichertemps(time(NULL)-m->temps, screen);

    if (GI->SecOpt)
        afficher_character(popt, screen);
    if (GI->lvl == 5 && (b->posmask.x >= 6200))
    {
        if (e->attack)
        {
            afficherAttack(*e, screen);
            attackPerso(e, screen);
        }
        else
            afficherEnnemi(*e, screen);
        animerCoin(coin);
        deplacer(e);
        afficher_ecran(1300, 800, coin->animation.spriteSheet[0], screen, &coin->animation.Clips[coin->animation.clipLoaded]); // afficher coin
    }

    /*if (collisionBB(p->offset, coin->pos) == 1)
    {
        printf("Collision detected!!\n");
    }*/
    // Collision Function
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if ((b->posmask.x >= 6890) && GI->lvl != 5)
    {
        m->pospoint.x = 400;
        m->pospoint.y = 80;
        *actpos = 6;
        GI->lvl++;
        b->posmask.x = 0;
        p->offset.x = 0;
        popt->offset.x = 0;
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
            b->image = IMG_Load("images/11night0.png");
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
            b->image = IMG_Load("images/11night1.png");
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
            b->image = IMG_Load("images/11night2.png");
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
            b->image = IMG_Load("images/11night3.png");
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
            b->image = IMG_Load("images/11night4.png");
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
    if (keystate[SDLK_p]){
        *actpos = 8;
    }
    if (keystate[SDLK_l]){
        *actpos = 7;
    }
    if (keystate[SDLK_UP])
    {
        jump(p, BD, B, GI, e, *coin, b, m, screen);
    }
    if (GI->SecOpt)
        if (keystate[SDLK_w])
        {
            jump(popt, BD, B, GI, e, *coin, b, m, screen);
        }


    SDL_PollEvent(&event);

    setcharacter(p, popt, keystate);

    changedirection(p, popt, m, b, GI->SecOpt);

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
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                x = event.button.x;
                y = event.button.y;
                if (x >= 760 && x <= 1159 && y >= 665 && y <= 784) // quit
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
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
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
                    {
                        return 2;
                    }
                    // load the game with the save
                    show_game(BD, B, GI, b, screen);

                    *actpos = 2;
                }
                if (x >= 760 && x <= 1159 && y >= 540 && y <= 659) // settings
                {
                    if (Mix_PlayChannel(-1, M->scratch, 0) == -1)
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
                    afficher_ecran(760, 665, B->menubtns_s[2], screen, NULL);
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
                    afficher_ecran(760, 413, B->resumebtn[1], screen, NULL);
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
                    afficher_ecran(760, 540, B->settingsbtnreal[1], screen, NULL);
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

void show_menu(btndim *BD, btn *B, menuitems *MI, settingsitems *SI, SDL_Surface *screen)
{
    afficher_ecran(0, 0, MI->background, screen, NULL);
    afficher_ecran(896.01, 305.14, MI->gamename, screen, NULL);
    afficher_ecran(625, 528, MI->btnreset, screen, NULL);
    if (B->isselected[0])
    {
        afficher_ecran(766, 534, B->menubtns_s[0], screen, NULL);
        afficher_ecran(684, 534, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 534, MI->rightarrow, screen, NULL);
    }
    if (B->isselected[1])
    {
        afficher_ecran(760, 680, B->menubtns_s[1], screen, NULL);
        afficher_ecran(684, 680, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 680, MI->rightarrow, screen, NULL);
    }
    if (B->isselected[2])
    {

        afficher_ecran(766, 814, B->menubtns_s[2], screen, NULL);
        afficher_ecran(684, 814, MI->leftarrow, screen, NULL);
        afficher_ecran(1175, 814, MI->rightarrow, screen, NULL);
    }
    if (B->isselected[3])
        afficher_ecran(1792, 24, B->menubtns_s[3], screen, NULL);
    else
        afficher_ecran(1792, 24, B->menubtns_u[3], screen, NULL);
    if (B->isselected[4])
        afficher_ecran(1636, 20, B->menubtns_s[4], screen, NULL);
    else
        afficher_ecran(1636, 20, B->menubtns_u[4], screen, NULL);
}

void show_pausemenu(btndim *BD, btn *B, menuitems *MI, gameitems *GI, pauseitems *PI, background *b, SDL_Surface *screen)
{
    show_game(BD, B, GI, b,screen);
    afficher_ecran(0, 0, PI->pausemenu, screen, NULL);
    afficher_ecran(760, 413, B->resumebtn[0], screen, NULL);
    afficher_ecran(760, 540, B->settingsbtnreal[0], screen, NULL);
    afficher_ecran(760, 665, B->menubtns_u[2], screen, NULL);
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
        afficher_ecran(b->posimage.x, b->posimage.y, b->image, screen, NULL);
}

void show_credits(btndim *BD, btn *B, menuitems *MI, settingsitems *SI, SDL_Surface *screen)
{
    afficher_ecran(584, 164, MI->credits, screen, NULL);
    afficher_ecran(776, 779, B->donebtn[0], screen, NULL);
}
void show_settings(btndim *BD, btn *B, settingsitems *SI, misc *M, SDL_Surface *screen)
{
    afficher_ecran(584, 164, SI->settings, screen, NULL);
    afficher_ecran(776, 779, B->donebtn[0], screen, NULL);
    if (B->isselected[6] == 0)
        afficher_ecran(776, 500, B->fsbtn[0], screen, NULL);
    else if (B->isselected[6])
        afficher_ecran(776, 500, B->fsbtn[2], screen, NULL);
    else
        afficher_ecran(776, 500, B->fsbtn[1], screen, NULL);
    FillRect(1207, 370, 14, 87, 0x979797, screen);
    FillRect(1187, 370, 14, 87, 0x979797, screen);
    FillRect(1167, 370, 14, 87, 0x979797, screen);
    FillRect(1147, 370, 14, 87, 0x979797, screen);
    FillRect(1127, 370, 14, 87, 0x979797, screen);
    FillRect(1107, 370, 14, 87, 0x979797, screen);
    switch (M->volume)
    {
    case 128:
        FillRect(1207, 370, 14, 87, 0x134908, screen);
    case 83:
        FillRect(1187, 370, 14, 87, 0x134908, screen);
    case 67:
        FillRect(1167, 370, 14, 87, 0x134908, screen);
    case 51:
        FillRect(1147, 370, 14, 87, 0x134908, screen);
    case 35:
        FillRect(1127, 370, 14, 87, 0x134908, screen);
    case 19:
        FillRect(1107, 370, 14, 87, 0x134908, screen);
        break;
    }
}