/*
 * File: sound.hpp
 * Phillip Chu
 * --------------
 * Provides an interface for
 * our sound processor object.
 */

#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

/* audioInfo - struct containing information about an
 * audio file */
struct audioInfo {
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 * wavBuffer;
	SDL_AudioDeviceID deviceID;
};

class soundProcessor {

	private:

        /* Maps filenames to audioInfo structs */
		std::unordered_map<std::string, audioInfo *> audioMap;
		audioInfo * loadAudio(std::string wavFile);

	public:

        /* Consructor - Loads all of the sound effects to the audioMap */
		soundProcessor() {
			SDL_Log("Creating sound processor...");
			audioMap["menu.wav"] = loadAudio("assets/sounds/menu.wav");
			audioMap["gameStart.wav"] = loadAudio("assets/sounds/gameStart.wav");
			audioMap["playerJump.wav"] = loadAudio("assets/sounds/playerJump.wav");
			audioMap["boneRattle.wav"] = loadAudio("assets/sounds/boneRattle.wav");
			audioMap["enemyDeath.wav"] = loadAudio("assets/sounds/enemyDeath.wav");
			audioMap["enemyAttack.wav"] = loadAudio("assets/sounds/enemyAttack.wav");
			audioMap["playerDamage.wav"] = loadAudio("assets/sounds/playerDamage.wav");
			audioMap["playerShoot.wav"] = loadAudio("assets/sounds/playerShoot.wav");
			audioMap["enemyDamage.wav"] = loadAudio("assets/sounds/enemyDamage.wav");
			audioMap["gameWin.wav"] = loadAudio("assets/sounds/gameWin.wav");
			audioMap["playerDeath.wav"] = loadAudio("assets/sounds/playerDeath.wav");
			audioMap["gameMusic.wav"] = loadAudio("assets/sounds/gameMusic.wav");
		}

        /* Destructor */
		~soundProcessor() {  
			std::unordered_map<std::string, audioInfo *>::iterator mit;
			for (mit = audioMap.begin(); mit != audioMap.end(); mit++) {
				SDL_CloseAudioDevice(mit->second->deviceID);
				SDL_FreeWAV(mit->second->wavBuffer);
				delete mit->second;
			}
		}

        /* playSound - plays a sound */
		void playSound(std::string wavFile);

        /* checkQueue - checks if a sound is currently playing */
		Uint32 checkQueue(std::string wavFile);

        /* stopSound - stops a sound effect */
		void stopSound(std::string wavFile);

        /* repeat - plays sound on repeat */
		void repeat(std::string wavFile);

};

#endif
