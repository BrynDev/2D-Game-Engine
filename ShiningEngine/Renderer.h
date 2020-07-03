#pragma once
#include "Singleton.h"
#include <SDL_Rect.h>

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

		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const noexcept { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

