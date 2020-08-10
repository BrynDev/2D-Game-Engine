#include "ShiningEnginePCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"

//static texture - constructor delegation
Shining::RenderComponent::RenderComponent(const std::string& textureName)
	:RenderComponent(textureName, 1, 0 ,0 ,0)
{
}

//sprite
Shining::RenderComponent::RenderComponent(const std::string& textureName, const int spriteScaleFactor, const int msPerFrame, const int nrRows, const int nrCols)
	: Component{}
	, m_pTexture{ Shining::ResourceManager::GetInstance().LoadTexture(textureName) }
	, m_SrcRect{0, 0, 0, 0}
	, m_ScaleFactor{spriteScaleFactor}
	, m_MsPerFrame{ msPerFrame }
	, m_NrRows{ nrRows }
	, m_NrCols{ nrCols }
	, m_MaxFrames{nrRows * nrCols}
	, m_CurrentFrame{0}
	, m_ElapsedTimeMs{0}
	, m_IsOscillating{false}
	, m_RotationAngle{0.f}
	, m_FlipFlag{SDL_FLIP_NONE}
{
	int textureWidth{};
	int textureHeight{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
	if (nrCols > 0) //I get warnings without these checks
	{
		m_SrcRect.w = textureWidth / nrCols;
	}
	else
	{
		m_SrcRect.w = textureWidth;
	}
	
	if (nrRows > 0)
	{
		m_SrcRect.h = textureHeight / nrRows;
	}	
	else
	{
		m_SrcRect.h = textureHeight;
	}
}

void Shining::RenderComponent::Render(const glm::vec2& pos) /*const*/
{
	if (m_NrCols == 0)
	{
		//this is a static texture
		Shining::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
	else
	{
		//this is a sprite
		//Shining::Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, SDL_Rect{ int(pos.x), int(pos.y), m_SrcRect.w * m_ScaleFactor, m_SrcRect.h * m_ScaleFactor});
		SDL_Rect dstRect{ int(pos.x), int(pos.y), m_SrcRect.w * m_ScaleFactor, m_SrcRect.h * m_ScaleFactor };
		Shining::Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, dstRect, m_RotationAngle, m_FlipFlag);
	}	
}

void Shining::RenderComponent::Update(const float timeStep) noexcept
{
	if (m_NrCols == 0) 
	{
		//if this is a static texture, early exit
		return;
	}

	m_ElapsedTimeMs += int(timeStep);

	if (m_ElapsedTimeMs >= m_MsPerFrame)
	{
		m_ElapsedTimeMs = 0;
		m_CurrentFrame += (int(!m_IsOscillating) * 2) - 1; //1 if false, -1 if true

		if(m_CurrentFrame >= m_NrCols - 1 || m_CurrentFrame <= 0) //if this is the final frame
		{			
			m_IsOscillating = !m_IsOscillating; //"move" in the opposite direction
		}

		m_SrcRect.x = m_CurrentFrame * m_SrcRect.w;	//update source rect
	}
}

void Shining::RenderComponent::RenderTile(const SDL_Rect& srcRect, const SDL_Rect& destRect) const noexcept
{
	Shining::Renderer::GetInstance().RenderTexture(*m_pTexture, srcRect, destRect);
}

void Shining::RenderComponent::SwapBuffer() noexcept
{
	//variables modified here aren't read outside of this class, no need to swap buffers
}

void Shining::RenderComponent::SetCurrentRow(const int rowIdx, const bool setColToZero) noexcept
{
	m_SrcRect.y = rowIdx * m_SrcRect.h;
	if (setColToZero)
	{
		m_SrcRect.x = 0;
	}
}

void Shining::RenderComponent::SetRotationAngle(const float angleDeg) noexcept
{
	m_RotationAngle = angleDeg;
}

void Shining::RenderComponent::SetFlipFlag(const RenderFlipFlag flag) noexcept
{
	switch (flag)
	{
	case RenderFlipFlag::none:
		m_FlipFlag = SDL_FLIP_NONE;
		break;
	case RenderFlipFlag::horizontal:
		m_FlipFlag = SDL_FLIP_HORIZONTAL;
		break;
	case RenderFlipFlag::vertical:
		m_FlipFlag = SDL_FLIP_VERTICAL;
		break;
	case RenderFlipFlag::diagonal:
		m_FlipFlag = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
		break;
	default:
		break;
	}
}

const Shining::RenderFlipFlag Shining::RenderComponent::GetFlipFlag() const noexcept
{
	switch (m_FlipFlag)
	{
	case SDL_FLIP_NONE:
		return RenderFlipFlag::none;
		break;
	case SDL_FLIP_HORIZONTAL:
		return RenderFlipFlag::horizontal;
		break;
	case SDL_FLIP_VERTICAL:
		return RenderFlipFlag::vertical;
		break;
	default:
		//diagonal flipflag is marked as a bitwise or between horizontal and vertical, this isnt valid syntax in a switch case so I return diagonal like this
		return RenderFlipFlag::diagonal;
		break;
	}
}

int Shining::RenderComponent::GetSpriteWidth() const noexcept
{
	return m_SrcRect.w * m_ScaleFactor;
}

int Shining::RenderComponent::GetSpriteHeight() const noexcept
{
	return m_SrcRect.h * m_ScaleFactor;
}