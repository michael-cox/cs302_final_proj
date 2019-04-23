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
#include "graphics.hpp"
#include "input.hpp"
#include "map.hpp"
#include "object.hpp"
#include "player.hpp"

class game
{
    private:

        menu * _mainMenu;
        graphicProcessor * _graphicProc;
        input * _inputProc;
        SDL_Texture * _background;

    public:

        /* Constructor - FULLSCREEN for fullscreen, SMALL for 800x450*/
        game(windowMode winMode);

        /* Deconstructor */
        ~game();

        /* Present render */
        void render();

        /* Run game */
        void runGame();

        void mainLoop();

        /* Map loading */
        //void loadMapFromText(std::string filename);

        /* Dump map in characters */
        //void dumpMap();

};

#endif
