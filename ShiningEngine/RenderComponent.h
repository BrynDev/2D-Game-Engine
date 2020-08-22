#pragma once
#include "Component.h"
#include <SDL_Rect.h>
#include <SDL_Render.h>

class Texture2D;

namespace Shining
{
	enum class RenderFlipFlag
	{
		none, horizontal, vertical, diagonal
	};

	class RenderComponent final : public Shining::Component
	{
	public:
		RenderComponent(const std::string& textureName, const int spriteScaleFactor);
		RenderComponent(const std::string& textureName, const int spriteScaleFactor, const int msPerFrame, const int nrRows, const int nrCols);
		virtual ~RenderComponent() = default;

		virtual void Render(const glm::vec2& pos) const override;
		virtual void Update(const float timeStep) noexcept override;
		virtual void SwapBuffer() noexcept override;
		void RenderTile(const SDL_Rect& srcRect, const SDL_Rect& destRect) const noexcept;
		void SetCurrentRow(const int rowIdx, const bool setColToZero) noexcept;
		void SetRotationAngle(const float angleDeg) noexcept;
		void SetFlipFlag(const RenderFlipFlag flag) noexcept;
		const RenderFlipFlag GetFlipFlag() const noexcept;
		int GetSpriteWidth() const noexcept;
		int GetSpriteHeight() const noexcept;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		Shining::Texture2D* m_pTexture;
		SDL_Rect m_SrcRect;
		const int m_ScaleFactor;
		//sprite data
		const int m_MsPerFrame;
		const int m_NrRows;
		const int m_NrCols;
		const int m_MaxFrames;
		int m_CurrentFrame;
		int m_ElapsedTimeMs;
		bool m_IsOscillating;
		float m_RotationAngle; //rotation performed on the destination rect
		SDL_RendererFlip m_FlipFlag; //flip performed on the texture
	};
}

