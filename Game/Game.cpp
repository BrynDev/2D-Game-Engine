#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "MoveRightCommand.h"
#include "MoveLeftCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "MoveState.h"
#include "IdleState.h"
#include "StartIdleCommand.h"
#include "ScoreObserver.h"
#include "PlayerCollision.h"
#include "PickupCollision.h"
#include "Enums.h"

int main()
{
	Shining::ShiningEngine engine{};	
	Shining::GameObject* pPlayerCharacter{ new Shining::GameObject(50,50) };	 
	pPlayerCharacter->AddComponent(new Shining::RenderComponent("Sprite_Car.png", 2, 80, 1, 3));
	pPlayerCharacter->AddComponent(new Shining::StateComponent(new IdleState(), pPlayerCharacter));
	pPlayerCharacter->GetComponent<Shining::StateComponent>()->AddState(new MoveState());
	pPlayerCharacter->AddComponent(new Shining::PhysicsComponent(pPlayerCharacter));
	pPlayerCharacter->AddComponent(new Shining::CollisionComponent(pPlayerCharacter, pPlayerCharacter->GetComponent<Shining::RenderComponent>(), int(CollisionTags::player))); //TEST / replace tag value with enum

	Shining::GameObject* pCollisionTest{ new Shining::GameObject(200,150) };
	pCollisionTest->AddComponent(new Shining::RenderComponent("blah.png", 2));
	pCollisionTest->AddComponent(new Shining::CollisionComponent(pCollisionTest, pCollisionTest->GetComponent<Shining::RenderComponent>(), int(CollisionTags::gem)));
	pCollisionTest->GetComponent<Shining::CollisionComponent>()->AddTargetTag(int(CollisionTags::player));

	Shining::CollisionBehavior* pPlayerCollision{ new PlayerCollision() };
	pPlayerCharacter->GetComponent<Shining::CollisionComponent>()->SetBehavior(pPlayerCollision);
	Shining::CollisionBehavior* pPickupCollision{ new PickupCollision() };
	pCollisionTest->GetComponent<Shining::CollisionComponent>()->SetBehavior(pPickupCollision);

	Shining::GameObject* pScoreboard{ new Shining::GameObject(200,30) };
	pScoreboard->AddComponent(new Shining::TextComponent("0", "Lingua.otf", SDL_Color{ 0,0,250 }, 50));
	pPlayerCharacter->AddObserver(new ScoreObserver(pScoreboard));
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

	/*Shining::GameObject* pPacman{ new Shining::GameObject(2,0) };
	Shining::GameObject* pGhost{ new Shining::GameObject(0,0) };
	pGhost->SetPosition(1, 0);
	if (pPacman->GetPosition().x - pGhost->GetPosition().x <= 1)
	{
		std::cout << "Pac caught\n";
	}
	pPacman->SetPosition(3, 0);

	glm::vec2 pacman{ 2,0 };
	glm::vec2 ghost{ 0,0 };
	
	ghost.x += 1;
	if (pacman.x - ghost.x <= 1)
	{
		std::cout << "Pac caught\n";
	}
	
	pacman.x += 1;
	delete pPacman;
	delete pGhost;*/
	


	engine.Run();
}
