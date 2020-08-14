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
	const int windowWidth{ 600 };
	const int windowHeight{ 400 };
	Shining::ShiningEngine engine{"Digger", windowWidth, windowHeight };

	Shining::GameObject* const pPlayerCharacter{ new Shining::GameObject(0,50) };
	{
		//init player components
		Shining::RenderComponent* const pPlayerRender{ new Shining::RenderComponent("DiggerCar.png", 2, 80, 1, 3) };
		pPlayerCharacter->AddComponent(pPlayerRender);
	
		Shining::StateComponent* const pPlayerState{ new Shining::StateComponent(new IdleState(), pPlayerCharacter) };
		pPlayerState->AddState(new MoveState());
		pPlayerCharacter->AddComponent(pPlayerState);

		Shining::PhysicsComponent* const pPlayerPhysics{ new Shining::PhysicsComponent(pPlayerCharacter) };
		pPlayerCharacter->AddComponent(pPlayerPhysics);

		Shining::CollisionComponent* const pPlayerCollision{ new Shining::CollisionComponent(pPlayerCharacter, pPlayerRender, int(CollisionTags::player), true, true) };
		Shining::CollisionBehavior* const pPlayerCollisionBehavior{ new PlayerCollision() };
		pPlayerCollision->SetBehavior(pPlayerCollisionBehavior);
	
		pPlayerCharacter->AddComponent(pPlayerCollision);
	}
	
	Shining::GameObject* pGemTest{ new Shining::GameObject(200,150) };
	{
		//init gem test components
		Shining::RenderComponent* const pGemRender{ new Shining::RenderComponent("Emerald.png", 2) };
		pGemTest->AddComponent(pGemRender);

		Shining::CollisionComponent* const pGemCollision{ new Shining::CollisionComponent(pGemTest, pGemRender, int(CollisionTags::gem), false, false) };
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

	const int wallSize{ 10 };
	const int wallOffset{ 2 }; //small offset that makes wall collision less strict
	Shining::GameObject* pLeftWall{ new Shining::GameObject(-wallSize - wallOffset, 0) };
	{
		Shining::CollisionComponent* pLeftWallCollision{ new Shining::CollisionComponent(pLeftWall, wallSize, windowHeight, int(CollisionTags::wall), false, false) };
		pLeftWallCollision->AddTargetTag(int(CollisionTags::player));
		pLeftWall->AddComponent(pLeftWallCollision);
	}

	Shining::GameObject* pRightWall{ new Shining::GameObject(windowWidth + wallOffset, 0) };
	{
		Shining::CollisionComponent* pRightWallCollision{ new Shining::CollisionComponent(pRightWall, wallSize, windowHeight, int(CollisionTags::wall), false, false) };
		pRightWallCollision->AddTargetTag(int(CollisionTags::player));
		pRightWall->AddComponent(pRightWallCollision);
	}

	Shining::GameObject* pBottomWall{ new Shining::GameObject(0, windowHeight + wallOffset) };
	{
		Shining::CollisionComponent* pBottomWallCollision{ new Shining::CollisionComponent(pBottomWall, windowWidth, wallSize, int(CollisionTags::wall), false, false) };
		pBottomWallCollision->AddTargetTag(int(CollisionTags::player));
		pRightWall->AddComponent(pBottomWallCollision);
	}

	Shining::GameObject* pTopWall{ new Shining::GameObject(0, -wallSize - wallOffset) };
	{
		Shining::CollisionComponent* pTopWallCollision{ new Shining::CollisionComponent(pTopWall, windowWidth, wallSize, int(CollisionTags::wall), false, false) };
		pTopWallCollision->AddTargetTag(int(CollisionTags::player));
		pRightWall->AddComponent(pTopWallCollision);
	}

	//create scenes
	Shining::Scene& scene{ engine.CreateScene("Game") };
	scene.Add(pPlayerCharacter);
	scene.Add(pScoreboard);
	scene.Add(pGemTest);
	scene.Add(pLeftWall);
	scene.Add(pRightWall);
	scene.Add(pBottomWall);
	scene.Add(pTopWall);
	scene.InitWorld("Tileset.png", "Level_1.csv", 20, 20, 4, 1, 15, 10);

	{
		//setup input and commands
		const float playerMoveSpeed{ 100.f };
		engine.RegisterPlayerCharacter(pPlayerCharacter);
		MoveRightCommand* const pMoveRight{ new MoveRightCommand(playerMoveSpeed) };
		MoveLeftCommand* const pMoveLeft{ new MoveLeftCommand(playerMoveSpeed) };
		MoveUpCommand* const pMoveUp{ new MoveUpCommand(playerMoveSpeed) };
		MoveDownCommand* const pMoveDown{ new MoveDownCommand(playerMoveSpeed) };
		StartIdleCommand* const pStartIdle{ new StartIdleCommand() };

		engine.AddCommand(pMoveRight, SDLK_d, Shining::ControllerInput::LeftStickRight);
		engine.AddCommand(pMoveLeft, SDLK_a, Shining::ControllerInput::LeftStickLeft);
		engine.AddCommand(pMoveUp, SDLK_w, Shining::ControllerInput::LeftStickUp);
		engine.AddCommand(pMoveDown, SDLK_s, Shining::ControllerInput::LeftStickDown);
		engine.SetNoInputCommand(pStartIdle);
	}

	engine.Run(); //here we go
}
