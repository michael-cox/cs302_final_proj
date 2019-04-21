/*
 * File: player.hpp
 * Michael Cox
 * ----------------
 * Provides an interface
 * for the player class.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

class player : public character
{
    private:
        /* TODO: std::vector<item> inventory */

        /* Temporary */
        SDL_Texture * _texture;
    public:
        /* TODO: void useItem(); */
        player(std::string name, int x, int y, imageProcessor * imgProc);
        void updateStatus(characterStatus newStatus);
        void move();
        void render();

};

#endif
