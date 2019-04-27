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

        /* Constructor */
		enemy(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc);

        /* Function to preload all of the animations */
        static void makeCache(graphicProcessor * graphicProc);

        /* Function to delete all loaded animations */
        static void clearCache();

        /* Updates the status of the enemy */
		void updateStatus(characterStatus newStatus);

        /* Moves the enemy based on their current status */
		void move();

        /* Renders the enemy */
		void render();

        /* Tells the enemy which direction to move */
		void seekPlayer(int playerX);

        /* Accessor functions to make collissions easier */
		int getX();
		int getY();
		int getW();
		int getH();
		void updateHealth();
		int checkHealth();

};




#endif

