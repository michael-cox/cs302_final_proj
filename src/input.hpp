/* Robert Smith
 * 4/14/19
 * CS 307 Final Project
 * input.hpp
 * Header file for input class.
 */
#include <SDL2/SDL.h>

class input {
	protected:
		//dont question newKey right now its for dumb testing purposes
		SDL_Event *event;
		SDL_Keycode key;
		//0 for neither, 1 for down, 2 for up
		bool direction;
	public:
		input() { event = new SDL_Event; }
		~input() { delete event; }
		SDL_Keycode readInput();
		bool readDirection();
};
