/*
 * File: sound.hpp
 * Phillip Chu
 * --------------
 *  Interface for using sounds.
 */

#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL2/SDL.h>
#include <string>

/*struct sound {
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 * wavBuffer;
	SDL_AudioDeviceID deviceID;
	int success;
};
*/

class soundProcessor {
	private:
		
	public:
		void playSound(std::string wavFile, int duration);
		
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 * wavBuffer;
	SDL_AudioDeviceID deviceID;
	int success;
};

#endif
