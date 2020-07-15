#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "JumpCommand.h"

int main()
{
	Shining::ShiningEngine engine{};	
	Shining::GameObject* pPlayerCharacter{ new Shining::GameObject() };	 
	pPlayerCharacter->AddComponent(new Shining::RenderComponent("Bub.png", 2, 100, 2, 4));

	Shining::Scene& scene{ engine.CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	engine.RegisterPlayerCharacter(pPlayerCharacter);
	engine.AddCommand(new JumpCommand(), SDLK_SPACE, Shining::ControllerInput::RightTrigger);
	engine.Run();
}
