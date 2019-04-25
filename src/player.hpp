/*
 * File: player.hpp
 * Michael Cox
 * ----------------
 * Provides an interface
 * for the player class.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include "character.hpp"
#include "sound.hpp"

#define PROJ_W 30
#define PROJ_H 12

class projectile : protected object {
	private:
		soundProcessor * _soundProc;
		sprite * _sprite;
		double _currVelocityX;
        direction _facing;
	public:
		projectile(int x, int y, graphicProcessor * graphicProc, direction facing) : object(x, y, PROJ_W, PROJ_H, true, graphicProc), _facing(facing) {
			if (facing == RIGHT) {
				_currVelocityX = 6;
				_sprite = new sprite("assets/ninja/png/kunaiRight.png", PNG, PROJ_W, PROJ_H, graphicProc);
			}
			else {
				_currVelocityX = -6;
				_sprite = new sprite("assets/ninja/png/kunaiLeft.png", PNG, PROJ_W, PROJ_H, graphicProc);
			}
		}
		~projectile() { delete _sprite; }
		bool move();
		void render();
};

class player : public character
{
    private:

		soundProcessor * _soundProc;
		std::list<projectile*> projList;

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
