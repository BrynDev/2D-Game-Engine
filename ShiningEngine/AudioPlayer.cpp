#include "ShiningEnginePCH.h"
#include "AudioPlayer.h"
#include <SDL_mixer.h>
#include "ResourceManager.h"
#include "SoundEffect.h"

void Shining::AudioPlayer::PlaySoundEffect(const std::string& fileName) const noexcept
{
	Shining::SoundEffect* pSound{ Shining::ResourceManager::GetInstance().LoadSoundEffect(fileName) };
	pSound->PlaySound();
}

const bool Shining::AudioPlayer::IsPlayingSoundEffect() const noexcept
{
	return(Mix_Playing(-1) == 0); //-1 counts the number of channels that are playing
}

void Shining::AudioPlayer::StopAllEffects() const noexcept
{
	Mix_HaltChannel(-1); //-1 to stop all channels
}

void Shining::AudioPlayer::SetAllEffectsVolume(const int volume) const noexcept
{
	Mix_Volume(-1, volume); //-1 to modify all channels
}

