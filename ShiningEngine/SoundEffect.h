#pragma once
//#include <SDL_mixer.h>

struct Mix_Chunk;

namespace Shining
{
	//RAII wrapper for an SDL_Chunk object
	class SoundEffect
	{
	public:
		explicit SoundEffect(Mix_Chunk* const pChunk);
		~SoundEffect();

		void PlaySound(const int nrRepeats = 0) const noexcept;
		void SetVolume(const int volume) const noexcept;

		

		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect& operator=(const SoundEffect& rhs) = delete;
		SoundEffect(SoundEffect&& other) = delete;
		SoundEffect& operator=(SoundEffect&& rhs) = delete;
	private:
		Mix_Chunk* const m_pSoundChunk;
	};

}
