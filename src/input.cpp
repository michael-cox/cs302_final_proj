/* Robert Smith
 * 4/14/19
 * CS307 Final Project
 * input.cpp
 * Definitions for prototypes in "input.hpp" as well as some minor testing.
 */
#include "input.hpp"

//Currently it handles one singular input at a time.
//SDLK_CALCULATOR is a trash key signifying we do not process the input
SDL_Keycode input::readInput() {
	SDL_PollEvent(event);
	//check if we process at all
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
		key = event->key.keysym.sym;
		//this is a little jank, may change later
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
		states[key].first = states[key].second;
		if (event->type == SDL_KEYDOWN) { states[key].second = 1; }
		else { states[key].second = 0; }
	
		if ((states[key].first ^ states[key].second) != 1) { key = SDLK_CALCULATOR; }
	}
	else { key = SDLK_CALCULATOR; }
	return key;
}

//Optional function for using boolean values in order to process the keys.
//Possibly may not be used as processing input as it is being taken in would
//be faster.
bool input::readDirection() {
	return states[key].second;
}
