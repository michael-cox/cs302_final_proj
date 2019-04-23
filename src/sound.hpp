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
		SDL_AudioSpec wavSpec;
		Uint32 wavLength;
		Uint8 * wavBuffer;
		SDL_AudioDeviceID deviceID;
	public:/*
		soundProcessor() {
			SDL_LoadWAV("assets/sounds/menu.wav", &wavSpec, &wavBuffer, &wavLength);
			deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
			SDL_QueueAudio(deviceID, wavBuffer, wavLength);
			SDL_PauseAudioDevice(deviceID, 0);
		}*/
		void playSound(std::string wavFile);
		Uint32 checkQueue();
		void stopSound();
		void repeat();
};

#endif
