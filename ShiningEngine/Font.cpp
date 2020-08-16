#include "ShiningEnginePCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Shining::Font::GetFont() const noexcept
{
	return m_Font;
}

unsigned int Shining::Font::GetSize() const noexcept
{
	return m_Size;
}

Shining::Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Shining::Font::~Font()
{
	TTF_CloseFont(m_Font);
}
