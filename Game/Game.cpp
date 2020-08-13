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

//"Perform every explicit resource allocation(e.g., new) in its own statement that immediately gives the
//allocated resource to a manager object(e.g., sharedptr); 
//otherwise, you can leak resources because the order of evaluation of a function's parameters is undefined.
// - "CPP Coding Standards - 101 Rules Guidelines and Best Practices 2005", item 13 - Herb Sutter, Andrei Alexandrescu

int main()
{
	Shining::ShiningEngine engine{};	
	Shining::GameObject* const pPlayerCharacter{ new Shining::GameObject(50,50) };
	{
		//init player components
		Shining::RenderComponent* const pPlayerRender{ new Shining::RenderComponent("Sprite_Car.png", 2, 80, 1, 3) };
		pPlayerCharacter->AddComponent(pPlayerRender);
	
		Shining::StateComponent* const pPlayerState{ new Shining::StateComponent(new IdleState(), pPlayerCharacter) };
		pPlayerState->AddState(new MoveState());
		pPlayerCharacter->AddComponent(pPlayerState);

		Shining::PhysicsComponent* const pPlayerPhysics{ new Shining::PhysicsComponent(pPlayerCharacter) };
		pPlayerCharacter->AddComponent(pPlayerPhysics);

		Shining::CollisionComponent* const pPlayerCollision{ new Shining::CollisionComponent(pPlayerCharacter, pPlayerRender, int(CollisionTags::player)) };
		Shining::CollisionBehavior* const pPlayerCollisionBehavior{ new PlayerCollision() };
		pPlayerCollision->SetBehavior(pPlayerCollisionBehavior);
	
		pPlayerCharacter->AddComponent(pPlayerCollision);
	}
	
	Shining::GameObject* pGemTest{ new Shining::GameObject(200,150) };
	{
		//init gem test components
		Shining::RenderComponent* const pGemRender{ new Shining::RenderComponent("blah.png", 2) };
		pGemTest->AddComponent(pGemRender);

		Shining::CollisionComponent* const pGemCollision{ new Shining::CollisionComponent(pGemTest, pGemRender, int(CollisionTags::gem)) };
		pGemCollision->AddTargetTag(int(CollisionTags::player));
		Shining::CollisionBehavior* const pPickupCollision{ new PickupCollision() };
		pGemCollision->SetBehavior(pPickupCollision);
		pGemTest->AddComponent(pGemCollision);
	}

	Shining::GameObject* pScoreboard{ new Shining::GameObject(200,30) };
	{
		//init scoreboard components
		Shining::TextComponent* const pScoreboardText{ new Shining::TextComponent("0", "Lingua.otf", SDL_Color{ 0,0,250 }, 50) };
		pScoreboard->AddComponent(pScoreboardText);

		ScoreObserver* pScoreObserver{ new ScoreObserver(pScoreboard) };
		pPlayerCharacter->AddObserver(pScoreObserver); //observe the player character, modify the scoreboard
	}

	//create scenes
	Shining::Scene& scene{ engine.CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	scene.Add(pScoreboard);
	scene.Add(pGemTest);
	scene.InitWorld("TestTileMap.png", "TestMap.csv", 33, 33, 8, 6, 15, 10);

	{
		//setup input and commands
		engine.RegisterPlayerCharacter(pPlayerCharacter);
		MoveRightCommand* const pMoveRight{ new MoveRightCommand() };
		MoveLeftCommand* const pMoveLeft{ new MoveLeftCommand() };
		MoveUpCommand* const pMoveUp{ new MoveUpCommand() };
		MoveDownCommand* const pMoveDown{ new MoveDownCommand() };
		StartIdleCommand* const pStartIdle{ new StartIdleCommand() };

		engine.AddCommand(pMoveRight, SDLK_d, Shining::ControllerInput::LeftStickRight);
		engine.AddCommand(pMoveLeft, SDLK_a, Shining::ControllerInput::LeftStickLeft);
		engine.AddCommand(pMoveUp, SDLK_w, Shining::ControllerInput::LeftStickUp);
		engine.AddCommand(pMoveDown, SDLK_s, Shining::ControllerInput::LeftStickDown);
		engine.SetNoInputCommand(pStartIdle);
	}

	engine.Run(); //here we go
}
