#pragma once
#include "Singleton.h"
#include <unordered_map>

namespace Shining
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);

		void Destroy();
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		//use maps to avoid allocating the same resource multiple times
		std::unordered_map<std::string, Texture2D*> m_TextureMap;
		//I use a multimap because 2 objects with the same font but different sizes are different objects, so same-key objects can exist
		std::unordered_multimap<std::string, Font*> m_FontMap; 
		std::string m_DataPath;
	};
}
