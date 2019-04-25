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
#include "sound.hpp"

class player : public character
{

    private:

		soundProcessor * _soundProc;
		direction _facing;

    public:

        /* Constructor */
        player(std::string name, int x, int y, graphicProcessor * graphicProc,
                soundProcessor * soundProc);

        /* Destructor */
        ~player();

        /* updateStatus - updates the player's status and sets their velocity, etc */
        void updateStatus(characterStatus newStatus);

        /* move - moves the player based on their velocity */
        void move();

        /* render - places the player on the screen */
        void render();

        /* getX - gets the x coordinate of the player */
        int getX();

};

#endif
