#include "ShiningEnginePCH.h"
#include "ShiningEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include <vector>

using namespace std;
using namespace std::chrono;

void Shining::ShiningEngine::Run()
{

	Renderer& renderer = Renderer::GetInstance();
	SceneManager& sceneManager = SceneManager::GetInstance();
	InputManager& input = InputManager::GetInstance();

	float realTimeElapsed{}; //this var can be [0,1] in case of small workload, integer instead of float means that elapsedTime can be 0 ms which is never accurate 		
	auto prevTime{ high_resolution_clock::now() };

	bool doContinue{ true };

	while (doContinue) //game loop
	{
		const auto currentTime = high_resolution_clock::now();
		const duration<float, milli> deltaTime{ currentTime - prevTime };
		prevTime = currentTime;
		realTimeElapsed += deltaTime.count();

		input.CheckForNewControllers(deltaTime.count());
		doContinue = input.ProcessInput(); //detect quit & take input
		sceneManager.SwapBuffer();

		//fixed update step
		while (realTimeElapsed >= MsPerFrame)
		{
			
			sceneManager.Update(MsPerFrame); //update game objects
			realTimeElapsed -= MsPerFrame;				
		}
		renderer.Render(); //render game objects
	}

	Cleanup();
}

Shining::ShiningEngine::ShiningEngine(const std::string& windowName, const int windowWidth, const int windowHeight)
{
	Initialize(windowName, windowWidth, windowHeight);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
}

void Shining::ShiningEngine::Initialize(const std::string& windowName, const int windowWidth, const int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		windowName.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void Shining::ShiningEngine::RegisterPlayerCharacter(GameObject* pPlayerCharacter) noexcept
{
	InputManager::GetInstance().RegisterPlayerCharacter(pPlayerCharacter);
}

/*void Shining::ShiningEngine::AddCommand(Command* const pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput) noexcept
{
	Shining::InputManager::GetInstance().AddCommand(pCommandToAdd, virtualKey, controllerInput);
}

void Shining::ShiningEngine::SetNoInputCommand(Command* pCommand) noexcept
{
	Shining::InputManager::GetInstance().SetNoInputCommand(pCommand);
}*/

void Shining::ShiningEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	SceneManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
}