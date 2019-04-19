/*
 * File: sound.cpp
 * Phillip Chu
 * ---------------
 *  Implements functions for playing
 *  sounds from sound.cpp
 */

#include <SDL2/SDL.h>
#include "sound.hpp"

void soundProcessor::playSound(string wavFile, int duration) {
	
	SDL_LoadWAV(wavFile, &wavSpec, &wavBuffer, &wavLength);

	SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	int success = SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceID, 0);

	SDL_Delay(duration);

	SDL_CLoseAudioDevice(deviceID);
	SDL_FreeWAV(wavBuffer);
	
	//SDL_Quit();
}
