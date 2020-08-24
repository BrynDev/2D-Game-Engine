#pragma once
#include "Singleton.h"
#include <SDL_Rect.h>
#include <SDL_Render.h>

struct SDL_Window;
struct SDL_Renderer;

namespace Shining
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) const; //render at given position with custom source rect (used for tiles and sprites)
		void RenderTexture(const Texture2D& texture, float x, float y) const; //render at given position
		void RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const; //render at given destRect
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect, const float angleDeg, const SDL_RendererFlip& flipFlag) const; //uses RenderCopyEX

		SDL_Renderer* GetSDLRenderer() const noexcept { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

