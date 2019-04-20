#include <SDL2/SDL.h>
#include "sound.hpp"

int main() {

	SDL_Init(SDL_INIT_EVERYTHING);

	soundProcessor sound;
	sound.playSound("../test/assets/sound/Powerup5.wav", 1000);	

	SDL_Quit();
}
