#include "ShiningEnginePCH.h"
#include "Texture2D.h"
#include <SDL.h>

Shining::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Shining::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Shining::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
