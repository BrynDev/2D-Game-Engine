#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "JumpCommand.h"
#include "MoveCommand.h"
#include "MoveState.h"
#include "IdleState.h"

int main()
{
	Shining::ShiningEngine engine{};	
	Shining::GameObject* pPlayerCharacter{ new Shining::GameObject(50,50) };	 
	pPlayerCharacter->AddComponent(new Shining::RenderComponent("Sprite_Car.png", 2, 80, 1, 3));
	pPlayerCharacter->AddComponent(new Shining::StateComponent(new IdleState(), pPlayerCharacter));
	pPlayerCharacter->GetComponent<Shining::StateComponent>()->AddState(new MoveState());
	Shining::PhysicsComponent* pPhysicsComponent{ new Shining::PhysicsComponent(pPlayerCharacter) };
	pPlayerCharacter->AddComponent(pPhysicsComponent);
	
	Shining::Scene& scene{ engine.CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	scene.InitWorld("TestTileMap.png", "TestMap.csv", 33, 33, 8, 6, 15, 10);

	engine.RegisterPlayerCharacter(pPlayerCharacter);
	engine.AddCommand(new JumpCommand(), SDLK_SPACE, Shining::ControllerInput::RightTrigger);
	engine.AddCommand(new MoveCommand(), SDLK_d, Shining::ControllerInput::LeftStickRight);
	engine.Run();
}
