#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <fstream>

namespace Shining
{
	class Texture2D;
	class Font;
	class SoundEffect;
	class Music;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file);
		SoundEffect* LoadSoundEffect(const std::string& file);
		Music* LoadMusic(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
		std::ifstream LoadFileForReading(const std::string& file) const;
		

		void Destroy();
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		//use maps to avoid allocating the same resource multiple times
		std::unordered_map<std::string, Texture2D*> m_TextureMap;
		//I use a multimap because 2 objects with the same font but different sizes are different objects, so same-key objects can exist
		std::unordered_multimap<std::string, Font*> m_FontMap; 
		std::unordered_map<std::string, SoundEffect*> m_SoundEffectMap;
		std::unordered_map<std::string, Music*> m_MusicMap;
		std::string m_DataPath;
	};
}
