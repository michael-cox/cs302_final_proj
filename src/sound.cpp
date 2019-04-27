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

/* Will initialize an audio device for a soundfile to accommodate for SDL's audio system */
audioInfo * soundProcessor::loadAudio(std::string wavFile) {
	audioInfo * temp = new audioInfo;
	SDL_LoadWAV(wavFile.c_str(), &(temp->wavSpec), &(temp->wavBuffer), &(temp->wavLength));
	temp->deviceID = SDL_OpenAudioDevice(NULL, 0, &(temp->wavSpec), NULL, 0);
	return temp;
}

/* Will play a given audio file */
void soundProcessor::playSound(std::string wavFile) {
	stopSound(wavFile);
	SDL_QueueAudio(audioMap[wavFile]->deviceID, audioMap[wavFile]->wavBuffer, audioMap[wavFile]->wavLength);
	SDL_PauseAudioDevice(audioMap[wavFile]->deviceID, 0);
}

/* Will stop a given audio file */
void soundProcessor::stopSound(std::string wavFile) {
	SDL_ClearQueuedAudio(audioMap[wavFile]->deviceID);
}

/* Will repeat an audio file */
void soundProcessor::repeat(std::string wavFile) {
	SDL_QueueAudio(audioMap[wavFile]->deviceID, audioMap[wavFile]->wavBuffer, audioMap[wavFile]->wavLength);	
}

/* Checks if a given song is currently playing */
Uint32 soundProcessor::checkQueue(std::string wavFile) {
	return SDL_GetQueuedAudioSize(audioMap[wavFile]->deviceID);
}
