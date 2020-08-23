#include "ShiningEnginePCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>

Shining::TextComponent::TextComponent(const std::string& text, const std::string& fontName, const SDL_Color& color, const int size)
	:TextComponent(text, fontName, color, size, 0, 0)
{
}

Shining::TextComponent::TextComponent(const std::string& text, const std::string& fontName, const SDL_Color& color, const int size, const int offsetX, const int offsetY)
	:Component{}
	, m_Text{ text }
	, m_pFont{ Shining::ResourceManager::GetInstance().LoadFont(fontName, size) }
	, m_Color{ color }
	, m_pTexture{ nullptr }
	, m_NeedsUpdate{ true }
	, m_OffsetX{ offsetX }
	, m_OffsetY{ offsetY }
{

}

Shining::TextComponent::~TextComponent()
{
	delete m_pTexture; //this texture was not loaded through the ResourceManager and must be deleted here
}

void Shining::TextComponent::Render(const glm::vec2& pos) const
{
	if (m_pTexture != nullptr)
	{
		Shining::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + m_OffsetX, pos.y + m_OffsetY);
	}
}

void Shining::TextComponent::Update(const float /*timeStep*/)
{
	//deltaTime is unused

	if (!m_NeedsUpdate)
	{
		return; //early exit
	}

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Shining::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (pTexture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	
	delete m_pTexture;
	m_pTexture = new Shining::Texture2D(pTexture);
	m_NeedsUpdate = false;	
}

void Shining::TextComponent::SwapBuffer() noexcept
{
	//member variables aren't read in other classes, no swap needed
}

void Shining::TextComponent::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}