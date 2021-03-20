#include "globals.h"
#include "soundmanager.h"
#include <vector>

SoundManager::SoundManager()
{
    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, AUDIO_S8, 2, 1024) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    loadAllMedia();
    Mix_VolumeMusic(MIX_MAX_VOLUME * 0.7);
    Mix_Volume(-1, MIX_MAX_VOLUME);
}

SoundManager::~SoundManager()
{
    std::multimap<std::string, Mix_Music*>::iterator it_music;
    for (it_music = _musicLibrary.begin(); it_music != _musicLibrary.end(); it_music++)
    {
        Mix_FreeMusic(it_music->second);
    }

    std::multimap<std::string, Mix_Chunk*>::iterator it_sfx;
    for (it_sfx = _sfxLibrary.begin(); it_sfx != _sfxLibrary.end(); it_sfx++)
    {
        Mix_FreeChunk(it_sfx->second);
    }
}

bool SoundManager::IsMusicPlaying()
{
    return Mix_PlayingMusic();
}

void SoundManager::PlayMusic(const std::string& songName, bool isLoop)
{
    if (Mix_PlayingMusic() == 0) {
        StopMusic();
    }

    if (_musicLibrary.count(songName) == 0) 
    {
        printf("Error: the song '%s' has not been loaded!\n", songName.c_str());
        return;
    }

    Mix_PlayMusic(_musicLibrary[songName], isLoop ? -1 : 0);
}

void SoundManager::StopMusic()
{
    Mix_HaltMusic();
}

void SoundManager::PlaySFX(const std::string& sfxName)
{
    Mix_PlayChannel(-1, _sfxLibrary[sfxName], 0);
}

bool SoundManager::loadAllMedia()
{
    bool success = true;

    // load music
    std::vector<std::string> musicNames =
    {
        "title",
        "level",
        "victory"
    };
    for (int i = 0; i < musicNames.size(); i++)
    {
        const std::string& filePath = "Assets/Audio/Music/" + std::to_string(i) + "_" + musicNames[i] + ".wav";
        _musicLibrary[musicNames[i]] = Mix_LoadMUS(filePath.c_str());
        if (_musicLibrary[musicNames[i]] == NULL)
        {
            printf("Failed to load music &s! SDL_mixer Error: %s\n", musicNames[i].c_str(), Mix_GetError());
            success = false;
        }
    }

    // load sound effects
    std::vector<std::string> sfxNames = 
    { 
        "title_confirm", 
        "step", 
        "error",
        "undo", 
        "reset",
        "stairs", 
        "death", 
        "button",
        "fall", 
        "bat"
    };
    for (int i = 0; i < sfxNames.size(); i++)
    {
        const std::string& filePath = "Assets/Audio/SFX/" + std::to_string(i) + "_" + sfxNames[i] + ".wav";
        _sfxLibrary[sfxNames[i]] = Mix_LoadWAV(filePath.c_str());
        if (_sfxLibrary[sfxNames[i]] == NULL)
        {
            printf("Failed to load sfx! SDL_mixer Error: %s\n", sfxNames[i].c_str(), Mix_GetError());
            success = false;
        }
    }
    return success;
}
