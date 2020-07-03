#pragma once
#include "Component.h"
#include <SDL_Rect.h>
class Texture2D;

namespace Shining
{
	class RenderComponent final : public Shining::Component
	{
	public:
		RenderComponent(const std::string& textureName);
		RenderComponent(const std::string& textureName, const int spriteScaleFactor, const int msPerFrame, const int nrRows, const int nrCols);
		virtual ~RenderComponent() = default;

		virtual void Render(const glm::vec3& pos) /*const*/ override;
		virtual void Update() noexcept override;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		Shining::Texture2D* m_pTexture;
		SDL_Rect m_SrcRect;
		const int m_ScaleFactor;
		const int m_MsPerFrame;
		const int m_NrRows;
		const int m_NrCols;
		const int m_MaxFrames;
		int m_CurrentFrame;
		int m_ElapsedTimeMs;
		bool m_IsOscillating;
	};
}

