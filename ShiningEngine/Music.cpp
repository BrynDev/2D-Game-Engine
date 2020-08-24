#include "ShiningEnginePCH.h"
#include "Music.h"
#include <SDL_mixer.h>

Shining::Music::Music(_Mix_Music* const pMusic)
	:m_pMusic{pMusic}
{
}

void Shining::Music::PlayMusic(const int nrPlays) const noexcept
{
	Mix_PlayMusic(m_pMusic, nrPlays);
}

Shining::Music::~Music()
{
	Mix_FreeMusic(m_pMusic);
}