#include "ShiningEnginePCH.h"
#include "AudioPlayer.h"
#include <SDL_mixer.h>
#include "ResourceManager.h"
#include "SoundEffect.h"
#include "Music.h"

void Shining::AudioPlayer::PlaySoundEffect(const std::string& fileName) const noexcept
{
	Shining::SoundEffect* pSound{ Shining::ResourceManager::GetInstance().LoadSoundEffect(fileName) };
	pSound->PlaySound();
}

void Shining::AudioPlayer::PlayMusic(const std::string& fileName, const int nrPlays) const noexcept
{
	Shining::Music* pMusic{ Shining::ResourceManager::GetInstance().LoadMusic(fileName) };
	pMusic->PlayMusic(nrPlays);
}

void Shining::AudioPlayer::PlayMusicLooped(const std::string& fileName) const noexcept
{
	Shining::Music* pMusic{ Shining::ResourceManager::GetInstance().LoadMusic(fileName) };
	pMusic->PlayMusic();
}

const bool Shining::AudioPlayer::IsPlayingSoundEffect() const noexcept
{
	return(Mix_Playing(-1) == 0); //-1 counts the number of channels that are playing
}

void Shining::AudioPlayer::StopAllEffects() const noexcept
{
	Mix_HaltChannel(-1); //-1 to stop all channels
}

void Shining::AudioPlayer::StopMusic() const noexcept
{
	Mix_HaltMusic();
}

void Shining::AudioPlayer::SetAllEffectsVolume(const int volume) const noexcept
{
	Mix_Volume(-1, volume); //-1 to modify all channels
}

void Shining::AudioPlayer::SetMusicVolume(const int volume) const noexcept
{
	Mix_VolumeMusic(volume);
}

