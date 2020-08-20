#pragma once
struct SDL_Window;

namespace Shining
{
	class Scene;
	class GameObject;

	class ShiningEngine
	{
	public:
		ShiningEngine(const std::string& windowName, const int windowWidth, const int windowHeight);
		void Initialize(const std::string& windowName, const int windowWidth, const int windowHeight);
		void Cleanup();
		void Run();

		//Delegate function calls to classes that aren't accessible from the game project
		void SetPlayer(GameObject* const pObjectToControl) noexcept;
		void SetKeyboardPlayer(GameObject* const pObjectToControl) noexcept;
		void SetControllerPlayer(GameObject* const pObjectToControl) noexcept;
		
		ShiningEngine(const ShiningEngine& other) = delete;
		ShiningEngine& operator=(const ShiningEngine& rhs) = delete;
		ShiningEngine(ShiningEngine&& other) = delete;
		ShiningEngine& operator=(ShiningEngine&& rhs) = delete;
	private:
		static const int MsPerFrame = 16;
		SDL_Window* m_Window{};

	};
}