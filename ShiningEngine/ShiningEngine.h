#pragma once
struct SDL_Window;
#include "Scene.h"

namespace Shining
{
	class ShiningEngine
	{
	public:
		ShiningEngine();
		void Initialize();
		void Cleanup();
		void Run();

		//Delegate function calls to classes that aren't accessible from the game project
		void RegisterPlayerCharacter(GameObject* pPlayerCharacter) noexcept;
		void AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput) noexcept;
		void SetNoInputCommand(Command* pCommand) noexcept; //Command to execute when no keys are pressed
		Scene& CreateScene(const std::string& name);

		ShiningEngine(const ShiningEngine& other) = delete;
		ShiningEngine& operator=(const ShiningEngine& rhs) = delete;
		ShiningEngine(ShiningEngine&& other) = delete;
		ShiningEngine& operator=(ShiningEngine&& rhs) = delete;
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}