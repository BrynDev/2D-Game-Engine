#pragma once
#include "Singleton.h"
#include <string>
#include <unordered_map>

namespace Shining
{
	class SoundEffect;

	class AudioPlayer final : public Singleton<AudioPlayer>
	{
	public:
		//void AddSoundEffect(const std::string& fileName) noexcept;
		void PlaySoundEffect(const std::string& fileName) const noexcept;

		void SetAllEffectsVolume(const int volume) const noexcept;
		void StopAllEffects() const noexcept;

	private:
		friend class Singleton<AudioPlayer>;
		AudioPlayer() = default;
	};


}
