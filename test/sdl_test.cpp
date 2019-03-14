/*
 * Michael Cox
 * March 11, 2019
 * File: sdl_test.cpp
 * ------------------
 * File to test making an sdl window
 * and things.
 */

#include <SDL2/SDL.h>   /* File to include for SDL */
#include <cassert>      /* File for C assertions */

int main(int argc, char **argv) /* argc and argv are apparently required by SDL2 */
{

    /* Initialize SDL. If SDL doesn't return 0, SDL fails and assert fails, program quits with
     * assert error */
    assert(!SDL_Init(SDL_INIT_EVERYTHING /* This can be any of a number of flags provided by the
                                            SDL bitwise OR'd (|) together that tell it what to
                                            initialize. */
                ));

    /* Initialize a window. If this fails, return nullptr, assert fails */
    SDL_Window * win = SDL_CreateWindow("Test", /* Window title C-style string */
            SDL_WINDOWPOS_CENTERED, /* X position flag - either this for center in X direction or
                                       SDL_WINDOWPOS_UNDEFINED for wherever OS decides to put it */
            SDL_WINDOWPOS_CENTERED, /*Y position flag - same */
            400, /* Width of window */
            400, /* Height of window */
            0 /* Place for flags - 0 for defaults */
            );
    assert(win != nullptr);

    /* Initialize a renderer that draws things */
    SDL_Renderer * ren = SDL_CreateRenderer(win, /* Window for renderer to act on */
            0, /* Index for to start at */
            0 /* Flags */
            );
    assert(ren != nullptr);

    /* Set the color for the renderer to draw with */
    SDL_SetRenderDrawColor(ren, /* Renderer to act on */
            0, /* Red */
            0, /* Green */
            0, /* Blue */
            0 /* Alpha */
            );

    /* Clear the screen with the draw color */
    SDL_RenderClear(ren);

    /* Load the current render stuff */
    SDL_RenderPresent(ren);

    /* Wait 10 seconds */
    SDL_Delay(10000);

    /* Quit */
    SDL_Quit();

    return 0;
}
