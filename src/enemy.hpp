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
        static std::unordered_map<characterStatus,animation*> _animationCache;

	public:
		enemy(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc);
        static void makeCache(graphicProcessor * graphicProc);
        static void clearCache();
		void updateStatus(characterStatus newStatus);
		void move();
		void render();
		void seekPlayer(int playerX);
		int getX();
		int getY();
		int getW();
		int getH();
		void updateHealth();
		int checkHealth();
};




#endif

