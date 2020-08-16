#include "ShiningEnginePCH.h"
#include "SoundEffect.h"
#include <SDL_mixer.h>


void Shining::SoundEffect::PlaySound(const int nrRepeats) const noexcept
{
	Mix_PlayChannel(-1, m_pSoundChunk, nrRepeats); //-1 to play on first available channel
}

void Shining::SoundEffect::SetVolume(const int volume) const noexcept
{
	Mix_VolumeChunk(m_pSoundChunk, volume);
}

Shining::SoundEffect::SoundEffect(Mix_Chunk* const pChunk)
	:m_pSoundChunk{pChunk}
{
}

Shining::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_pSoundChunk);
}