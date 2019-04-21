/*
 * Michael Cox
 * CS302 March 14, 2019
 * File: game_object.hpp
 * -----------------------
 * An object oriented SDL window
 * handler.
 */

#ifndef GAME_OBJ_HPP
#define GAME_OBJ_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include "menu.hpp"
#include "image.hpp"
#include "input.hpp"
#include "map.hpp"
#include "object.hpp"
#include "player.hpp"

class GWin
{
    private:
        static bool _isInit;
        static size_t _numInst;
        SDL_Window * _win;
        SDL_Renderer * _ren;
        SDL_DisplayMode * _display;
        SDL_Texture * _background;
        Map * _map;
        imageProcessor * imgProc;
        input * keyInput;

    public:

        /* Constructors */
        GWin(std::string windowTitle);
        GWin(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);

        /* Deconstructor */
        ~GWin();

        /* SDL initializer */
        void initSDL();

        /* Get display mode */
        void getDisplayMode();

        /* Create window functions */
        void createWindow(std::string windowTitle);
        void createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);

        /* Texture importing functions */
        void importIMG(std::string imgPath, imageType imgType);

        /* Render texture */
        void renderTexture(std::string textureName, int x, int y);

        /* Render an animation */
        void renderTextureAnimation(std::string textureName, int frameWidth, int frameNum, int x, int y);

        /* Present render */
        void render();

        /* Run game */
        void runGame();

        /* Map loading */
        void loadMapFromText(std::string filename);

        /* Dump map in characters */
        void dumpMap();

        void loadMainMenu();

};

#endif
