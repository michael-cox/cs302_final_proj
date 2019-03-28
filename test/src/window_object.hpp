/*
 * Michael Cox
 * CS302 March 14, 2019
 * File: game_object.hpp
 * -----------------------
 * An object oriented SDL window
 * handler
 */

#ifndef GAME_OBJ_HPP
#define GAME_OBJ_HPP

#include <SDL2/SDL.h>
#include <string>

class GWin
{
    private:
        static bool isInit;
        SDL_Window * win;
        SDL_Renderer * ren;
    public:

        /* Constructors */
        GWin() : win(nullptr), ren(nullptr) {}
        GWin(std::string windowTitle);
        GWin(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        GWin(std::string windowTitle, double percentOfScreen, uint32_t windowFlags);

        /* Deconstructor */
        ~GWin();

        /* SDL initializer */
        void initSDL();

        /* Create window functions */
        void createWindow(std::string windowTitle);
        void createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        void createWindow(std::string windowTitle, double percentOfScreen, uint32_t windowFlags);

        /* 

};

#endif
