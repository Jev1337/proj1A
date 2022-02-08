#include "timer.h"

void timer(Timer *T)
{
    T->startTicks = 0;
    T->pausedTicks = 0;
    T->paused = 0;
    T->started = 0;
}
void start(Timer *T)
{
    // Start the timer
    T->started = 1;

    // Unpause the timer
    T->paused = 0;

    // Get the current clock time
    T->startTicks = SDL_GetTicks();
}

void stop(Timer *T)
{
    // Stop the timer
    T->started = 0;

    // Unpause the timer
    T->paused = 0;
}

int get_ticks(Timer *T)
{
    // If the timer is running
    if (T->started == 1)
    {
        // If the timer is paused
        if (T->paused == 1)
        {
            // Return the number of ticks when the timer was paused
            return T->pausedTicks;
        }
        else
        {
            // Return the current time minus the start time
            return SDL_GetTicks() - T->startTicks;
        }
    }

    // If the timer isn't running
    return 0;
}

void pauses(Timer *T)
{
    // If the timer is running and isn't already paused
    if ((T->started == 1) && (T->paused == 1))
    {
        // Pause the timer
        T->paused = 1;

        // Calculate the paused ticks
        T->pausedTicks = SDL_GetTicks() - T->startTicks;
    }
}

void unpause(Timer *T)
{
    // If the timer is paused
    if (T->paused == 1)
    {
        // Unpause the timer
        T->paused = 0;

        // Reset the starting ticks
        T->startTicks = SDL_GetTicks() - T->pausedTicks;

        // Reset the paused ticks
        T->pausedTicks = 0;
    }
}

int is_started(Timer *T)
{
    return T->started;
}
int is_paused(Timer *T)
{
    return T->paused;
}