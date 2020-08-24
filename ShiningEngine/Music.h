#pragma once

//struct Mix_Music;
struct _Mix_Music;

namespace Shining
{
	class Music
	{
	public:
		explicit Music(_Mix_Music* const pMusic);
		~Music();

		void PlayMusic(const int nrPlays = -1) const noexcept; //-1 plays this music until stopped
		//void SetVolume(const int volume) const noexcept;

		Music(const Music& other) = delete;
		Music& operator=(const Music& rhs) = delete;
		Music(Music&& other) = delete;
		Music& operator=(Music&& rhs) = delete;
	private:
		_Mix_Music* m_pMusic;
	};

}

