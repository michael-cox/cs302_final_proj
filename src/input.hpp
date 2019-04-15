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
		bool KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_Z, KEY_ESC;
		SDL_Event *event;
		//0 for neither, 1 for down, 2 for up
		char direction;
	public:
		input() : KEY_UP(0), KEY_DOWN(0), KEY_LEFT(0), KEY_RIGHT(0), KEY_SPACE(0), KEY_Z(0), KEY_ESC(0) { event = new SDL_Event; }
		~input() { delete event; }
		void readInput();
		void processKeys();
};
