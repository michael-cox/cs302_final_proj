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
#include <unordered_map>

/*struct sound {
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 * wavBuffer;
	SDL_AudioDeviceID deviceID;
	int success;
};
*/

struct audioInfo {
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 * wavBuffer;
	SDL_AudioDeviceID deviceID;
};

class soundProcessor {
	private:
		std::unordered_map<std::string, audioInfo *> audioMap;
		audioInfo * loadAudio(std::string wavFile);
	public:
		soundProcessor() {
			SDL_Log("Making sound processor...");
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
		}
		~soundProcessor() {  
			std::unordered_map<std::string, audioInfo *>::iterator mit;
			for (mit = audioMap.begin(); mit != audioMap.end(); mit++) {
				SDL_CloseAudioDevice(mit->second->deviceID);
				SDL_FreeWAV(mit->second->wavBuffer);
				delete mit->second;
			}
		}
		void playSound(std::string wavFile);
		Uint32 checkQueue(std::string wavFile);
		void stopSound(std::string wavFile);
		void repeat(std::string wavFile);
};

#endif
