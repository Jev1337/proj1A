#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <string.h>
typedef struct
{
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    int paused;
    int started;
}Timer;

    void timer(Timer *T);
    //The various clock actions
    void start(Timer *T);
    void stop(Timer *T);
    void pauses(Timer *T);
    void unpause(Timer *T);
    
    //Gets the timer's time
    int get_ticks(Timer *T);
    
    //Checks the status of the timer
    int is_started(Timer *T);
    int is_paused(Timer *T);    


#endif // MENU_H_INCLUDED