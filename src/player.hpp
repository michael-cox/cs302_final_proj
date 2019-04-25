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


class projectile : protected object {
	private:
		soundProcessor * _soundProc;
		direction _facing;
		sprite * _sprite;
		double _currVelocityX;
	public:
		projectile(int x, int y, graphicProcessor * graphicProc, direction facing) : object(x, y, 15, 6, true, graphicProc), _facing(facing) {
			if (facing == RIGHT) {
				_currVelocityX = 6;
				_sprite = new sprite("assets/ninja/png/kunaiRight.png", PNG, 100, 100, graphicProc);
			}
			else {
				_currVelocityX = -6;
				_sprite = new sprite("assets/ninja/png/kunaiLeft.png", PNG, 100, 100, graphicProc);
			}
		}
		~projectile() { delete _sprite; }
		void move();
		void render();
};

class player : public character
{
    private:

		soundProcessor * _soundProc;
		direction _facing;
		std::vector<projectile*> projList;
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
};

#endif
