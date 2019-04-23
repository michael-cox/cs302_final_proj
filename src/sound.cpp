/*
 * File: sound.cpp
 * Phillip Chu
 * ---------------
 *  Implements functions for playing
 *  sounds from sound.cpp
 */

#include <SDL2/SDL.h>
#include "sound.hpp"
#include <string>

void soundProcessor::playSound(std::string wavFile) {
	
	SDL_LoadWAV(wavFile.c_str(), &wavSpec, &wavBuffer, &wavLength);
	
	deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	int success = SDL_QueueAudio(deviceID, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceID, 0);

//	SDL_Delay(duration);

//	SDL_CloseAudioDevice(deviceID);
//	SDL_FreeWAV(wavBuffer);
	
	//SDL_Quit();
}

void soundProcessor::stopSound() {
	SDL_CloseAudioDevice(deviceID);
	SDL_FreeWAV(wavBuffer);
}

void soundProcessor::repeat() {
	SDL_QueueAudio(deviceID, wavBuffer, wavLength);	
}

Uint32 soundProcessor::checkQueue() {
	return SDL_GetQueuedAudioSize(deviceID);
}
