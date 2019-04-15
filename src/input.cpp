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
void input::readInput() {
	SDL_PollEvent(event);
	//Check if it is what we want
	if (event->key.state == SDL_PRESSED) { direction = 1; }
	else if (event->key.state == SDL_RELEASED) { direction = 2; }
	else { direction = 0; }
	//check if we process a key at all
	//couts are for testing
	if (direction) {
		switch (event->key.keysym.sym) {
			case SDLK_LEFT:
				if (direction == 1) { 
					KEY_LEFT = 1;
					std::cout << "am going left\n";
				}
				else { 
					KEY_LEFT = 0; 
					std::cout << "am no longer going left\n";
				}
				break;
			case SDLK_RIGHT:
				if (direction == 1) { 
					KEY_RIGHT = 1; 
					std::cout << "this is right, right?\n";
				}
				else { 
					KEY_RIGHT = 1; 
					std::cout << "right doesnt exit anymore\n";
				}
				break;
			case SDLK_UP: 
				if (direction == 1) { 
					KEY_UP = 1; 
					std::cout << "wupwards time\n";
				}
				else { 
					KEY_UP = 0; 
					std::cout << "wupwards has expired\n";
				}
				break;
			case SDLK_DOWN:
				if (direction == 1) { 
					KEY_DOWN = 1; 
					std::cout << "lets go downtown\n";
				}
				else { 
					KEY_DOWN = 0; 
					std::cout << "no more downtown\n";
				}
				break;
			case SDLK_SPACE:
				if (direction == 1) { 
					KEY_SPACE = 1; 
					std::cout << "i think we need some space\n";
				}
				else { 
					KEY_SPACE = 0; 
					std::cout << "too much space\n";
				}
				break;
			case SDLK_z:
				if (direction == 1) { 
					KEY_Z = 1; 
					std::cout << "pewpewpewpew (you are pressing the z key)\n";
				}
				else { 
					KEY_Z = 0; 
					std::cout << "click click (you are no longer pressing the z key)\n";
				}
				break;
			case SDLK_ESCAPE:
				if (direction == 1) { 
					KEY_ESC = 1; 
					std::cout << "OH SHIT GETOUT WE DIPPIN\n";
				}
				else { 
					KEY_ESC = 0; 
					std::cout << "technically this message shouldnt been seen cause its quit\n";
				}
				break;
		}
	}
}

//Optional function for using boolean values in order to process the keys.
//Possibly may not be used as processing input as it is being taken in would
//be faster.
void input::processKeys() {
	if (KEY_ESC) {
		SDL_Quit();
		exit(1);
	}
}

//this doesnt work right now cause I'm too lazy to make a window right now
//but I will do it. The inputs should be fine though
int main (int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
	input test;
	while (1) {
		SDL_RenderPresent(ren);
		test.readInput();
		test.processKeys();
	}
}
