#pragma once
#include <SDL_mixer.h>
#include <string>
#include <map>

class SoundManager
{
public:
	static SoundManager* instance;

	SoundManager();
	~SoundManager();

	bool IsMusicPlaying();

	void PlayMusic(const std::string& songName, bool isLoop = false);
	void StopMusic();

	void PlaySFX(const std::string& sfxName);
private:
	bool loadAllMedia();
	std::map<std::string, Mix_Music*> _musicLibrary;
	std::map <std::string, Mix_Chunk*> _sfxLibrary;
};