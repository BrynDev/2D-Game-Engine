#include "ShiningEnginePCH.h" //single include to access all engine functionality
#include "MoveRightCommand.h"
#include "MoveLeftCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "StartIdleCommand.h"
#include "StartGameCommand.h"
//#include "StartGameKeyboardCommand.h"  -- test these later
//#include "StartGameControllerCommand.h"
#include "MoveState.h"
#include "IdleState.h"

#include "ScoreObserver.h"
#include "LevelChangeObserver.h"
#include "PlayerCollision.h"
#include "PickupCollision.h"
#include "Enums.h"

//"Perform every explicit resource allocation(e.g., new) in its own statement that immediately gives the
//allocated resource to a manager object(e.g., sharedptr); 
//otherwise, you can leak resources because the order of evaluation of a function's parameters is undefined.
// - "CPP Coding Standards - 101 Rules Guidelines and Best Practices 2005", item 13 - Herb Sutter, Andrei Alexandrescu

void AddGemToScene(Shining::Scene* const pSceneToAddTo, const float xPos, const float yPos );

int main()
{
	const int windowWidth{ 600 };
	const int windowHeight{ 440 };
	Shining::ShiningEngine engine{"Digger", windowWidth, windowHeight };
	Shining::SceneManager& sceneManager{ Shining::SceneManager::GetInstance() };
	const int tileSize{ 20 };
	const int worldScale{ 2 };
	const int scaledTileSize{ tileSize * worldScale }; //by multiplying ints with this value I can essentially place objects on specific tiles
	const int nrTilesetCols{ 4 };
	const int nrTilesetRows{ 1 };
	const int nrWorldCols{ 15 };
	const int nrWorldRows{ 10 };
	const int worldWidth{ nrWorldCols * scaledTileSize };
	const int worldHeight{ nrWorldRows * scaledTileSize };

	//player
	Shining::GameObject* const pPlayerCharacter{ new Shining::GameObject(7 * scaledTileSize , 9 * scaledTileSize + 2) }; //+2 so the player doesn't clip some dirt at the start
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
	
	Shining::GameObject* const pScoreboard{ new Shining::GameObject(50, worldHeight) };
	{
		//text component
		Shining::TextComponent* const pScoreboardText{ new Shining::TextComponent("0", "Retro Gaming.ttf", SDL_Color{ 0,250,0 }, 25) };
		pScoreboard->AddComponent(pScoreboardText);

		//observer
		ScoreObserver* pScoreObserver{ new ScoreObserver(pScoreboard) };
		pPlayerCharacter->AddObserver(pScoreObserver); //observe the player character, modify the scoreboard
	}

	LevelChangeObserver* pLevelChangeObserver{ new LevelChangeObserver() };
	pPlayerCharacter->AddObserver(pLevelChangeObserver);
	

	const int wallSize{ 10 };
	const int wallOffset{ 2 }; //small offset that makes wall collision less strict
	Shining::GameObject* pLeftWall{ new Shining::GameObject(-wallSize - wallOffset, 0) };
	{
		Shining::CollisionComponent* pLeftWallCollision{ new Shining::CollisionComponent(pLeftWall, wallSize, worldHeight, int(CollisionTags::wall), false, false) };
		pLeftWallCollision->AddTargetTag(int(CollisionTags::player));
		pLeftWall->AddComponent(pLeftWallCollision);
	}

	Shining::GameObject* pRightWall{ new Shining::GameObject(worldWidth + wallOffset, 0) };
	{
		Shining::CollisionComponent* pRightWallCollision{ new Shining::CollisionComponent(pRightWall, wallSize, worldHeight, int(CollisionTags::wall), false, false) };
		pRightWallCollision->AddTargetTag(int(CollisionTags::player));
		pRightWall->AddComponent(pRightWallCollision);
	}

	Shining::GameObject* pBottomWall{ new Shining::GameObject(0, worldHeight + wallOffset) };
	{
		Shining::CollisionComponent* pBottomWallCollision{ new Shining::CollisionComponent(pBottomWall, worldWidth, wallSize, int(CollisionTags::wall), false, false) };
		pBottomWallCollision->AddTargetTag(int(CollisionTags::player));
		pRightWall->AddComponent(pBottomWallCollision);
	}

	Shining::GameObject* pTopWall{ new Shining::GameObject(0, -wallSize - wallOffset) };
	{
		Shining::CollisionComponent* pTopWallCollision{ new Shining::CollisionComponent(pTopWall, worldWidth, wallSize, int(CollisionTags::wall), false, false) };
		pTopWallCollision->AddTargetTag(int(CollisionTags::player));
		pRightWall->AddComponent(pTopWallCollision);
	}

	//menu scene
	Shining::Scene* pMenuScene{ sceneManager.CreateScene("Menu") };
	{
		Shining::GameObject* pStartMenu{ new Shining::GameObject(0,0) };
		Shining::RenderComponent* pMenuRender{ new Shining::RenderComponent("TitleScreen.png", 2) };
		pStartMenu->AddComponent(pMenuRender);
		pMenuScene->Add(pStartMenu);

		const int textSize{ 20 };
		Shining::GameObject* pTitle{ new Shining::GameObject((windowWidth / 2) - textSize, 8) };
		Shining::TextComponent* pTitleText{ new Shining::TextComponent("DIGGER", "Retro Gaming.ttf", SDL_Color{10,230,10}, textSize) };
		pTitle->AddComponent(pTitleText);
		pMenuScene->Add(pTitle);
	}

	//game level 1 scene
	Shining::Scene* pGameScene_Level1{ sceneManager.CreateScene("Game_Level1") };
	{
		//these objects are in in most scenes
		pGameScene_Level1->Add(pPlayerCharacter);
		pGameScene_Level1->Add(pScoreboard);
		pGameScene_Level1->Add(pLeftWall);
		pGameScene_Level1->Add(pRightWall);
		pGameScene_Level1->Add(pBottomWall);
		pGameScene_Level1->Add(pTopWall);

		//these objects are unique to this scene
		//this essentially puts the gem on top of the tile on column idx 3 row idx 1
		AddGemToScene(pGameScene_Level1, 3 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 4 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 7 * scaledTileSize, 1 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 3 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 4 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 7 * scaledTileSize, 2 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 3 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 4 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 7 * scaledTileSize, 3 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 3 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 4 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 7 * scaledTileSize, 4 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 3 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 4 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 7 * scaledTileSize, 5 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 12 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 13 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 14 * scaledTileSize, 3 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 12 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 13 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 14 * scaledTileSize, 4 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 12 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 13 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 14 * scaledTileSize, 5 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 0 * scaledTileSize, 8 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 14 * scaledTileSize, 8 * scaledTileSize);

		AddGemToScene(pGameScene_Level1, 0 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 1 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 13 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level1, 14 * scaledTileSize, 9 * scaledTileSize);

		pLevelChangeObserver->AddGemGoal(30); //pick up 30 gems to proceed to next stage

		pGameScene_Level1->InitWorld("Tileset.png", "Level_1.csv", worldScale, tileSize, tileSize, nrTilesetCols, nrTilesetRows, nrWorldCols, nrWorldRows);
	}

	//game level 2 scene
	Shining::Scene* pGameScene_Level2{ sceneManager.CreateScene("Game_Level2") };
	{
		pGameScene_Level2->Add(pPlayerCharacter);
		pGameScene_Level2->Add(pScoreboard);
		pGameScene_Level2->Add(pLeftWall);
		pGameScene_Level2->Add(pRightWall);
		pGameScene_Level2->Add(pBottomWall);
		pGameScene_Level2->Add(pTopWall);

		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 2 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 2 * scaledTileSize, 2 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 7 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 8 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 9 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 10 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 11 * scaledTileSize, 2 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 2 * scaledTileSize, 3 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 7 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 8 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 9 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 10 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 11 * scaledTileSize, 3 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 0 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 2 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 3 * scaledTileSize, 4 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 0 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 2 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 3 * scaledTileSize, 5 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 2 * scaledTileSize, 6 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 7 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 8 * scaledTileSize, 6 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 6 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 7 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 8 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 9 * scaledTileSize, 7 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 12 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 13 * scaledTileSize, 7 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 0 * scaledTileSize, 8 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 7 * scaledTileSize, 8 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 8 * scaledTileSize, 8 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 12 * scaledTileSize, 8 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 13 * scaledTileSize, 8 * scaledTileSize);

		AddGemToScene(pGameScene_Level2, 0 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level2, 1 * scaledTileSize, 9 * scaledTileSize);
		pLevelChangeObserver->AddGemGoal(41);

		pGameScene_Level2->InitWorld("Tileset.png", "Level_2.csv", worldScale, tileSize, tileSize, nrTilesetCols, nrTilesetRows, nrWorldCols, nrWorldRows);
	}

	//game level 3 scene
	Shining::Scene* pGameScene_Level3{ sceneManager.CreateScene("Game_Level3") };
	{
		pGameScene_Level3->Add(pPlayerCharacter);
		pGameScene_Level3->Add(pScoreboard);
		pGameScene_Level3->Add(pLeftWall);
		pGameScene_Level3->Add(pRightWall);
		pGameScene_Level3->Add(pBottomWall);
		pGameScene_Level3->Add(pTopWall);

		AddGemToScene(pGameScene_Level3, 0 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 1 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 6 * scaledTileSize, 1 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 8 * scaledTileSize, 1 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 0 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 6 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 8 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 12 * scaledTileSize, 2 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 2 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 6 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 8 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 11 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 12 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 3 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 14 * scaledTileSize, 3 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 0 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 1 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 2 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 3 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 6 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 8 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 11 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 12 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 4 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 14 * scaledTileSize, 4 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 0 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 1 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 2 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 3 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 12 * scaledTileSize, 5 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 5 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 1 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 2 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 5 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 9 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 12 * scaledTileSize, 6 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 6 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 1 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 2 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 5 * scaledTileSize, 7 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 9 * scaledTileSize, 7 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 0 * scaledTileSize, 8 * scaledTileSize);	
		AddGemToScene(pGameScene_Level3, 5 * scaledTileSize, 8 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 9 * scaledTileSize, 8 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 14 * scaledTileSize, 8 * scaledTileSize);

		AddGemToScene(pGameScene_Level3, 0 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 1 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 14 * scaledTileSize, 9 * scaledTileSize);

		pLevelChangeObserver->AddGemGoal(49);

		pGameScene_Level3->InitWorld("Tileset.png", "Level_3.csv", worldScale, tileSize, tileSize, nrTilesetCols, nrTilesetRows, nrWorldCols, nrWorldRows);
	}
	
	//setup input and commands
	//menu screen input
	{
		Shining::InputContext* pMenuInput{ new Shining::InputContext() };
		StartGameCommand* const pStartGame{ new StartGameCommand() };

		pMenuInput->AddCommand(pStartGame, SDLK_SPACE, Shining::ControllerInput::ButtonA);
		pMenuInput->AddCommand(pStartGame, SDLK_LEFT, Shining::ControllerInput::LeftStickLeft);
		pMenuInput->AddCommand(pStartGame, SDLK_RIGHT, Shining::ControllerInput::LeftStickRight);
		pMenuInput->AddCommand(pStartGame, SDLK_UP, Shining::ControllerInput::LeftStickUp);
		pMenuInput->AddCommand(pStartGame, SDLK_DOWN, Shining::ControllerInput::LeftStickDown);

		pMenuScene->InitInputContext(pMenuInput);
	}
	//game input
	{	
		const float playerMoveSpeed{ 100.f };
		engine.SetPlayer(pPlayerCharacter);
		
		MoveRightCommand* const pMoveRight{ new MoveRightCommand(playerMoveSpeed) };
		MoveLeftCommand* const pMoveLeft{ new MoveLeftCommand(playerMoveSpeed) };
		MoveUpCommand* const pMoveUp{ new MoveUpCommand(playerMoveSpeed) };
		MoveDownCommand* const pMoveDown{ new MoveDownCommand(playerMoveSpeed) };
		StartIdleCommand* const pStartIdle{ new StartIdleCommand() };

		Shining::InputContext* pGameInput{ new Shining::InputContext() };
		pGameInput->AddCommand(pMoveRight, SDLK_RIGHT, Shining::ControllerInput::LeftStickRight);
		pGameInput->AddCommand(pMoveLeft, SDLK_LEFT, Shining::ControllerInput::LeftStickLeft);
		pGameInput->AddCommand(pMoveUp, SDLK_UP, Shining::ControllerInput::LeftStickUp);
		pGameInput->AddCommand(pMoveDown, SDLK_DOWN, Shining::ControllerInput::LeftStickDown);
		pGameInput->SetNoInputCommand(pStartIdle);

		pGameScene_Level1->InitInputContext(pGameInput);
		pGameScene_Level2->InitInputContext(pGameInput);
		pGameScene_Level3->InitInputContext(pGameInput);
	}

	sceneManager.SetScene(pMenuScene);
	engine.Run(); //here we go
}

void AddGemToScene(Shining::Scene* const pSceneToAddTo, const float xPos, const float yPos )
{
	Shining::GameObject* pGem{ new Shining::GameObject(xPos,yPos) };

	//render component
	Shining::RenderComponent* const pGemRender{ new Shining::RenderComponent("Emerald.png", 2) };
	pGem->AddComponent(pGemRender);

	//collision component
	Shining::CollisionComponent* const pGemCollision{ new Shining::CollisionComponent(pGem, pGemRender, int(CollisionTags::gem), false, false) };
	pGemCollision->AddTargetTag(int(CollisionTags::player));
	Shining::CollisionBehavior* const pPickupCollision{ new PickupCollision() };
	pGemCollision->SetBehavior(pPickupCollision);
	pGem->AddComponent(pGemCollision);

	pSceneToAddTo->Add(pGem);
}