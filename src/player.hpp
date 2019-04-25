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
		/* TODO: std::vector<item> inventory */

		/* Temporary */
		double _g;
		double _gVelocity;
		soundProcessor * _soundProc;
		direction _facing;
		std::vector<projectile*> projList;
	public:
		/* TODO: void useItem(); */
		player(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc);
		~player();
		void updateStatus(characterStatus newStatus);
		void move();
		void render();

};

#endif
