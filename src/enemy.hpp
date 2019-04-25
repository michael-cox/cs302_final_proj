/*
 * File: enemy.hpp
 * Phllip Chu
 * ---------------
 *  Provides an interface
 *  for the enemy class.
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include "character.hpp"
#include "sound.hpp"

class enemy : public character
{
	private:
		soundProcessor * _soundProc;

	public:
		enemy(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc);
		~enemy();
		void updateStatus(characterStatus newStatus);
		void move();
		void render();
		void seekPlayer(int playerX);
};




#endif

