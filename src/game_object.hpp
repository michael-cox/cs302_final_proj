/*
 * Michael Cox
 * CS302 March 14, 2019
 * File: game_object.hpp
 * -----------------------
 * An object handling the
 * game itself.
 */

#ifndef GAME_OBJ_HPP
#define GAME_OBJ_HPP

#include <SDL2/SDL.h>
#include <string>
#include "menu.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "map.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "wall.hpp"
#include "sound.hpp"

class game
{
    private:
        menu * _mainMenu;
        graphicProcessor * _graphicProc;
        input * _inputProc;
		soundProcessor * _soundProc;
        SDL_Texture * _background;
        int _w, _h;
        map * _map;
        player * _player;

		enemy * _enemy;

        std::vector<object*> _objects;

    public:

        /* Constructor - FULLSCREEN for fullscreen, SMALL for  */
        game(windowMode winMode);

        /* Deconstructor */
        ~game();

        /* render - clears the screen, copies all the necessary textures to the window, and presents them */
        void render();

        /* runGame - the single function that loads the menu and subsequently the game itself */
        void runGame();

        /* mainLoop - the loop of the game itself */
        void mainLoop();

        /* placeWall - places a single wall at the specified location */
        void placeWall(int x, int y, wallType type);

		bool checkCollision(std::list<projectile*> projList);

};

#endif
