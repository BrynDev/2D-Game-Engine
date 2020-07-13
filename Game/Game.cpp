#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "JumpCommand.h"

int main()
{
	Shining::ShiningEngine engine{};
	//same path specified as in ShiningEngine.cpp but doesn't work here
	//initialization is instead done in ShiningEngine.cpp for the sake of the presentation
	engine.SetDataPath("../Data/"); 
	
	Shining::GameObject* pPlayerCharacter{ new Shining::GameObject() };
	 
	//pPlayerCharacter->AddComponent(new Shining::RenderComponent("Bub.png", 2, 100, 2, 4)); //Loading a sprite from here doesn't work
	Shining::Scene& scene{ Shining::SceneManager::GetInstance().CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	engine.RegisterPlayerCharacter(pPlayerCharacter);
	engine.AddCommand(new JumpCommand(), SDLK_SPACE, Shining::ControllerInput::RightTrigger);
	engine.Run();
}
