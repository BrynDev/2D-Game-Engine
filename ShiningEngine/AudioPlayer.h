#pragma once
#include "Singleton.h"
#include <string>

namespace Shining
{
	class SoundEffect;

	class AudioPlayer final : public Singleton<AudioPlayer>
	{
	public:
		void PlaySoundEffect(const std::string& fileName) const noexcept;
		void PlayMusic(const std:: string& fileName, const int nrPlays) const noexcept;
		void PlayMusicLooped(const std::string& fileName) const noexcept;

		const bool IsPlayingSoundEffect() const noexcept;
		void StopAllEffects() const noexcept;
		void StopMusic() const noexcept;
		
		void SetAllEffectsVolume(const int volume) const noexcept;
		void SetMusicVolume(const int volume) const noexcept;
	private:
		friend class Singleton<AudioPlayer>;
		AudioPlayer() = default;
	};


}
