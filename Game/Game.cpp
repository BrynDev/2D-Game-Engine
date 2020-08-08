#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "MoveRightCommand.h"
#include "MoveLeftCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "MoveState.h"
#include "IdleState.h"
#include "StartIdleCommand.h"
#include "ScoreObserver.h"

int main()
{
	Shining::ShiningEngine engine{};	
	Shining::GameObject* pPlayerCharacter{ new Shining::GameObject(50,50) };	 
	pPlayerCharacter->AddComponent(new Shining::RenderComponent("Sprite_Car.png", 2, 80, 1, 3));
	pPlayerCharacter->AddComponent(new Shining::StateComponent(new IdleState(), pPlayerCharacter));
	pPlayerCharacter->GetComponent<Shining::StateComponent>()->AddState(new MoveState());
	pPlayerCharacter->AddComponent(new Shining::PhysicsComponent(pPlayerCharacter));
	pPlayerCharacter->AddComponent(new Shining::CollisionComponent(&(pPlayerCharacter->GetPosition()), pPlayerCharacter->GetComponent<Shining::RenderComponent>(), 0, true)); //TEST / replace tag value with enum

	Shining::GameObject* pCollisionTest{ new Shining::GameObject(200,150) };
	pCollisionTest->AddComponent(new Shining::RenderComponent("DefaultTexture.jpg"));
	pCollisionTest->AddComponent(new Shining::CollisionComponent(&(pCollisionTest->GetPosition()), pCollisionTest->GetComponent<Shining::RenderComponent>(), 1, true));
	pCollisionTest->GetComponent<Shining::CollisionComponent>()->AddTargetTag(0);
	pCollisionTest->GetComponent<Shining::CollisionComponent>()->AddTargetTag(2);


	Shining::GameObject* pScoreboard{ new Shining::GameObject(200,30) };
	pScoreboard->AddComponent(new Shining::TextComponent("0", "Lingua.otf", SDL_Color{ 0,0,250 }, 50));
	pPlayerCharacter->AddObserver(new ScoreObserver(pScoreboard)); //TEST
	Shining::Scene& scene{ engine.CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	scene.Add(pScoreboard);
	scene.Add(pCollisionTest);
	scene.InitWorld("TestTileMap.png", "TestMap.csv", 33, 33, 8, 6, 15, 10);

	engine.RegisterPlayerCharacter(pPlayerCharacter);
	engine.AddCommand(new MoveRightCommand(), SDLK_d, Shining::ControllerInput::LeftStickRight);
	engine.AddCommand(new MoveLeftCommand(), SDLK_a, Shining::ControllerInput::LeftStickLeft);
	engine.AddCommand(new MoveUpCommand(), SDLK_w, Shining::ControllerInput::LeftStickUp);
	engine.AddCommand(new MoveDownCommand(), SDLK_s, Shining::ControllerInput::LeftStickDown);
	engine.SetNoInputCommand(new StartIdleCommand());

	engine.Run();
}
