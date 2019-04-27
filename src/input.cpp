/* Robert Smith
 * 4/14/19
 * CS307 Final Project
 * input.cpp
 * Definitions for prototypes in "input.hpp" as well as some minor testing.
 */
#include "input.hpp"

/* Reads in a single key press. If it is not a key that we would usually process, 
 * we return the calculator key to signify it is  a trash input */
SDL_Keycode input::readInput() {
	SDL_PollEvent(event);
	/* Check if it is a keypress event */
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
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
		/* States[].first holds a prev state and states[].second holds the current state.
		 * this is to check if the key switches states, if not return trash key */
		states[key].first = states[key].second;
		if (event->type == SDL_KEYDOWN) { states[key].second = 1; }
		else { states[key].second = 0; }
	
		if ((states[key].first ^ states[key].second) != 1) { key = SDLK_CALCULATOR; }
	}
	else { key = SDLK_CALCULATOR; }
	return key;
}

/* Returns the state of the key that was just pressed or released */
bool input::readDirection() {
	return states[key].second;
}
