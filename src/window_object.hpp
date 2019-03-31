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

#define GWIN_WIDTH 1280
#define GWIN_HEIGHT 720

class GWin
{
    private:
        static bool _isInit;
        SDL_Window * _win;
        SDL_Renderer * _ren;
        SDL_DisplayMode _display;
    public:

        /* Constructors */
        GWin() : _win(nullptr), _ren(nullptr) {}
        GWin(std::string windowTitle);
        GWin(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        /* TODO: GWin(std::string windowTitle, double percentOfScreen, uint32_t windowFlags); */

        /* Deconstructor */
        ~GWin();

        /* SDL initializer */
        void initSDL();

        /* Get display mode */
        void getDisplayMode();

        /* Create window functions */
        void createWindow(std::string windowTitle);
        void createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        /* TODO: void createWindow(std::string windowTitle, double percentOfScreen, uint32_t windowFlags); */

        /* Render BMP */
        SDL_Texture * loadBMP(std::string imagePath, int x, int y);

        /* Render style sheet */
        void renderStyleSheet(std::string ssPath, int frameWidth, int x, int y);

        /* Run game */
        void runGame();

};

#endif
