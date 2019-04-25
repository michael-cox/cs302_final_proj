/*
 * File: input.hpp
 * Robert Smith
 * ---------------
 * Interface for the input
 * object that handles all
 * game input.
 */

#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <utility>

class input {

	protected:

		SDL_Event *event;
		SDL_Keycode key;

		/* Maps key to a pair of the previous state and current state */
		std::unordered_map<SDL_Keycode, std::pair<bool, bool> > states;

	public:

        /* Constructor */
		input() { event = new SDL_Event; }

        /* Destructor */
		~input() { delete event; }

        /* readInput - reads a keyboard event and returns the key, returning the
         * calculator key if no entry */
		SDL_Keycode readInput();

        /* readDirection - returns true if the key was pressed down, false if unpressed */
		bool readDirection();

};

#endif
