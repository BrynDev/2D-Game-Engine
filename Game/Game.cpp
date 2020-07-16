#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "JumpCommand.h"

int main()
{
	Shining::ShiningEngine engine{};	
	Shining::GameObject* pPlayerCharacter{ new Shining::GameObject() };	 
	pPlayerCharacter->AddComponent(new Shining::RenderComponent("Sprite_Car.png", 2, 80, 1, 3));

	Shining::Scene& scene{ engine.CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	engine.RegisterPlayerCharacter(pPlayerCharacter);
	engine.AddCommand(new JumpCommand(), SDLK_SPACE, Shining::ControllerInput::RightTrigger);
	engine.Run();
}
