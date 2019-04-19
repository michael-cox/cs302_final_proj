/* Robert Smith
 * 4/14/19
 * CS307 Final Project
 * input.cpp
 * Definitions for prototypes in "input.hpp" as well as some minor testing.
 */
#include "input.hpp"
#include <iostream>

//Currently it handles one singular input at a time.
//Updating the boolean variables will act as filler for actual character action.
SDL_Keycode input::readInput() {
	SDL_PollEvent(event);
	//check if we process at all
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
		if (event->type == SDL_KEYDOWN) { direction = 1;  }
		else { direction = 0; }
		key = event->key.keysym.sym;
		switch (key) {
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_UP: 
				break;
			case SDLK_DOWN:
				break;
			case SDLK_SPACE:
				break;
			case SDLK_z:
				break;
			case SDLK_ESCAPE:
				break;
			case SDLK_RETURN:
				break;
			default:
				key = SDLK_CALCULATOR;
				break;
		}
	}
	return key;
}

//Optional function for using boolean values in order to process the keys.
//Possibly may not be used as processing input as it is being taken in would
//be faster.
bool input::readDirection() {
	return direction;
}
