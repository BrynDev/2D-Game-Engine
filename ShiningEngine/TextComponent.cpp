#include "ShiningEnginePCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>

Shining::TextComponent::TextComponent(const std::string& text, const std::string& fontName, const SDL_Color& color, const int size)
	:Component{}
	, m_Text{text}
	, m_pFont{ Shining::ResourceManager::GetInstance().LoadFont(fontName, size)}
	, m_Color{color}
	, m_pTexture{nullptr}
	, m_NeedsUpdate{true}
{

}

Shining::TextComponent::~TextComponent()
{
	delete m_pTexture; //this texture was not loaded through the ResourceManager and must be deleted here
}

void Shining::TextComponent::Render(const glm::vec2& pos) /*const*/
{
	if (m_pTexture != nullptr)
	{
		Shining::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void Shining::TextComponent::Update(const float /*timeStep*/)
{
	//deltaTime is unused

	if (m_NeedsUpdate)
	{
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
		//allocations and deletions should not be in an update function, is there an alternative to this?
		delete m_pTexture;
		m_pTexture = new Shining::Texture2D(pTexture);
		m_NeedsUpdate = false;
	}
}

void Shining::TextComponent::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}