/* Robert Smith
 * 4/14/19
 * CS 307 Final Project
 * input.hpp
 * Header file for input class.
 */

#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <unordered_map>
#include <utility>

class input {
	protected:
		//dont question newKey right now its for dumb testing purposes
		SDL_Event *event;
		SDL_Keycode key;
		//key, prevState, currState
		std::unordered_map<SDL_Keycode, std::pair<bool, bool> > states;
	public:
		input() { event = new SDL_Event; }
		~input() { delete event; }
		SDL_Keycode readInput();
		bool readDirection();
};

#endif
