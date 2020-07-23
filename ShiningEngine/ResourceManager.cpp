#include "ShiningEnginePCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include <algorithm>

void Shining::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

void Shining::ResourceManager::Destroy()
{
	for (std::pair<const std::string, Font*> element : m_FontMap)
	{
		delete element.second;
	}
	for (std::pair<const std::string, Texture2D*> element : m_TextureMap)
	{
		delete element.second;
	}
}

Shining::Texture2D* Shining::ResourceManager::LoadTexture(const std::string& file)
{
	const std::string fullPath{ m_DataPath + file };
	SDL_Texture* pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	try
	{
		if (pTexture == nullptr)
		{
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
		}
	}
	catch (const std::runtime_error& exception)
	{
		//load a default texture instead and continue running
		std::cout << exception.what() << std::endl;
		const std::string defaultPath{ m_DataPath + "DefaultTexture.jpg" };
		pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), defaultPath.c_str());
	}

	//check if this texture has already been loaded
	if (m_TextureMap.find(fullPath) != m_TextureMap.cend())
	{
		return m_TextureMap.at(fullPath);
	}
	else
	{
		Texture2D* pNewTexture{ new Texture2D(pTexture) };
		m_TextureMap.insert(std::make_pair(fullPath, pNewTexture));
		return pNewTexture;
	}
}

Shining::Font* Shining::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	const std::string fullPath{ m_DataPath + file };
	
	//check if this font has already been loaded
	using range = std::pair<std::unordered_multimap<std::string, Font*>::iterator, std::unordered_multimap<std::string, Font*>::iterator>;
	range sameNameRange{ m_FontMap.equal_range(fullPath) };
	if (sameNameRange.first != m_FontMap.cend()) 
	{
		//font name found
		//also check if sizes are the same -> different size is different object
		Font* pFoundFont{ nullptr }; //if this font is already loaded, store in pFoundFont and return it
		bool isFontNew{ true };
		std::for_each(sameNameRange.first, sameNameRange.second, [&pFoundFont, &isFontNew, size](std::pair<std::string, Font*> pair) {
			if (pair.second->GetSize() == size)
			{
				isFontNew = false;
				pFoundFont = pair.second;
				return;
			}
		});

		if (!isFontNew)
		{
			return pFoundFont; //return already loaded font
		}		
	}

	//this is a new font
	Font* pNewFont{ new Font(fullPath, size) };
	m_FontMap.insert(std::make_pair(fullPath, pNewFont)); //add it to the map
	return pNewFont;
	
}

std::ifstream Shining::ResourceManager::LoadFileForReading(const std::string& file) const
{
	std::ifstream ifStream{ m_DataPath + file };
	return ifStream;
}
