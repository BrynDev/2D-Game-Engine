#include "ShiningEnginePCH.h" //single include to access all engine functionality

#include "MoveRightCommand.h"
#include "MoveLeftCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include "StartIdleCommand.h"
#include "StartGameCommand.h"
#include "ShootCommand.h"

#include "MoveState.h"
#include "IdleState.h"
#include "DyingState.h"
#include "BagIdleState.h"
#include "BagWarningState.h"
#include "BagFallingState.h"
#include "ShotReadyState.h"
#include "ShotCooldownState.h"

#include "ScoreObserver.h"
#include "LevelChangeObserver.h"
#include "LifeObserver.h"

#include "PlayerHit.h"
#include "PlayerCollision.h"
#include "PickupCollision.h"
#include "BagCollision.h"
#include "FireBallCollision.h"
#include "EnemyCollision.h"
#include "Enums.h"

//"Perform every explicit resource allocation(e.g., new) in its own statement that immediately gives the
//allocated resource to a manager object(e.g., sharedptr); 
//otherwise, you can leak resources because the order of evaluation of a function's parameters is undefined.
// - "CPP Coding Standards - 101 Rules Guidelines and Best Practices 2005", item 13 - Herb Sutter, Andrei Alexandrescu

void AddGemToScene(Shining::Scene* const pSceneToAddTo, const float xPos, const float yPos );
void AddGoldBagToScene(Shining::Scene* const pSceneToAddTo, Shining::HealthComponent* const pPlayerHealth, const float xPos, const float yPos);
void AddEnemyToScene(Shining::Scene* const pSceneToAddTo, LevelChangeObserver* const pLevelChangeObs, ScoreObserver* const pScoreObs, const float xPos, const float yPos);

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

	
	//fireball
	Shining::GameObject* const pFireball{ new Shining::GameObject(-150.f,0.f) }; //object will be moved to player's location upon activation
	{
		//render
		Shining::RenderComponent* const pFireballRender{ new Shining::RenderComponent("Fireball.png", 2, 20, 1, 3) };
		pFireball->AddComponent(pFireballRender);
		//collision
		Shining::CollisionComponent* const pFireballCollision{ new Shining::CollisionComponent(pFireball, pFireballRender, int(CollisionTags::fireBall), true, false) };
		pFireballCollision->AddTargetTag(int(CollisionTags::goldBag));
		pFireballCollision->AddTargetTag(int(CollisionTags::wall));
		pFireballCollision->AddTargetTag(int(CollisionTags::enemy));
		Shining::CollisionBehavior* const pFireballCollisionBehavior{ new FireballCollision() };
		pFireballCollision->SetBehavior(pFireballCollisionBehavior);
		pFireball->AddComponent(pFireballCollision);
		//physics
		Shining::PhysicsComponent* const pFireballPhysics{ new Shining::PhysicsComponent(pFireball, false) };
		pFireball->AddComponent(pFireballPhysics);	
	}

	//player
	Shining::GameObject* const pPlayerCharacter{ new Shining::GameObject(7 * scaledTileSize , 9 * scaledTileSize + 2) }; //+2 so the player doesn't clip some dirt at the start
	Shining::HealthComponent* const pPlayerHealth{ new Shining::HealthComponent(pPlayerCharacter, 99, 3) }; //player can earn more lives
	
	{
		//render
		Shining::RenderComponent* const pPlayerRender{ new Shining::RenderComponent("DiggerCar.png", 2, 80, 3, 3) };
		pPlayerCharacter->AddComponent(pPlayerRender);
		//state
		Shining::State* const pIdleState{ new IdleState() };
		Shining::StateComponent* const pPlayerState{ new Shining::StateComponent(pIdleState, pPlayerCharacter) };
		Shining::State* const pMoveState{ new MoveState() };
		pPlayerState->AddState(pMoveState);
		Shining::State* const pDyingState{ new DyingState() };
		pPlayerState->AddState(pDyingState);
		//second layer of state
		Shining::State* const pShotReadyState{ new ShotReadyState() };
		Shining::State* const pShotCooldownState{ new ShotCooldownState() };
		pPlayerState->AddNewStateLayer(pShotReadyState);
		pPlayerState->AddState(pShotCooldownState, 1); //add to second state layer
		pPlayerCharacter->AddComponent(pPlayerState);
		//physics
		Shining::PhysicsComponent* const pPlayerPhysics{ new Shining::PhysicsComponent(pPlayerCharacter, false) };
		pPlayerCharacter->AddComponent(pPlayerPhysics);
		//collision
		Shining::CollisionComponent* const pPlayerCollision{ new Shining::CollisionComponent(pPlayerCharacter, pPlayerRender, int(CollisionTags::player), true, true) };
		Shining::CollisionBehavior* const pPlayerCollisionBehavior{ new PlayerCollision() };
		pPlayerCollision->SetBehavior(pPlayerCollisionBehavior);
		pPlayerCharacter->AddComponent(pPlayerCollision);
		//spawner, for the fireball object
		Shining::SpawnComponent* const pFireballSpawner{ new Shining::SpawnComponent(pFireball, true) };
		pPlayerCharacter->AddComponent(pFireballSpawner);
		//health
		Shining::HitBehavior* const pPlayerHitBehavior{ new PlayerHit() };
		pPlayerHealth->SetHitBehavior(pPlayerHitBehavior);
		pPlayerCharacter->AddComponent(pPlayerHealth);

	}
	//level change observer
	LevelChangeObserver* pLevelChangeObserver{ new LevelChangeObserver() };
	pPlayerCharacter->AddObserver(pLevelChangeObserver);

	//scoreboard
	Shining::GameObject* const pScoreboard{ new Shining::GameObject(50, worldHeight) };
	Shining::TextComponent* const pScoreboardText{ new Shining::TextComponent("0", "Retro Gaming.ttf", SDL_Color{ 0,250,0 }, 25) };
	pScoreboard->AddComponent(pScoreboardText);
	
	//score observer
	ScoreObserver* pScoreObserver{ new ScoreObserver(pScoreboardText) };
	pPlayerCharacter->AddObserver(pScoreObserver); //observe the player character, modify the scoreboard
	
	//lives counter
	Shining::GameObject* const pLivesCounter{ new Shining::GameObject(145, worldHeight + 5) }; //slight offset to make it look nicer
	{
		Shining::RenderComponent* const pLivesRender{ new Shining::RenderComponent("Life.png", 2) };
		pLivesCounter->AddComponent(pLivesRender);

		Shining::TextComponent* const pLivesText{ new Shining::TextComponent("x 3", "Retro Gaming.ttf", SDL_Color{ 0,250,0 }, 18, 35, 0) };
		pLivesCounter->AddComponent(pLivesText);
		//life observer
		LifeObserver* const pLifeObserver{ new LifeObserver(pLivesText) };
		pPlayerCharacter->AddObserver(pLifeObserver);
	}
	
	//walls
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
		pBottomWall->AddComponent(pBottomWallCollision);
	}

	Shining::GameObject* pTopWall{ new Shining::GameObject(0, -wallSize - wallOffset) };
	{
		Shining::CollisionComponent* pTopWallCollision{ new Shining::CollisionComponent(pTopWall, worldWidth, wallSize, int(CollisionTags::wall), false, false) };
		pTopWallCollision->AddTargetTag(int(CollisionTags::player));
		pTopWall->AddComponent(pTopWallCollision);
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
		pGameScene_Level1->Add(pFireball);
		pGameScene_Level1->Add(pPlayerCharacter);	
		pGameScene_Level1->Add(pScoreboard);
		pGameScene_Level1->Add(pLivesCounter);
		pGameScene_Level1->Add(pLeftWall);
		pGameScene_Level1->Add(pRightWall);
		pGameScene_Level1->Add(pBottomWall);
		pGameScene_Level1->Add(pTopWall);

		//these objects are unique to this scene
		
		//GEMS
		AddGemToScene(pGameScene_Level1, 3 * scaledTileSize, 1 * scaledTileSize); //this essentially puts the gem on top of the tile on column idx 3 row idx 1
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

		//GOLD BAGS
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 4 * scaledTileSize, 0 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 12 * scaledTileSize, 1 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 1 * scaledTileSize, 2 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 5 * scaledTileSize, 3 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 8 * scaledTileSize, 3 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 6 * scaledTileSize, 6 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level1, pPlayerHealth, 8 * scaledTileSize, 6 * scaledTileSize);

		//ENEMY
		AddEnemyToScene(pGameScene_Level1, pLevelChangeObserver, pScoreObserver, 14 * scaledTileSize, 0 * scaledTileSize);

		pLevelChangeObserver->AddGemGoal(30); //pick up 30 gems to proceed to next stage
		pLevelChangeObserver->AddEnemyKillsGoal(1); // kill 1 enemy to proceed to next stage

		pGameScene_Level1->InitWorld("Tileset.png", "Level_1.csv", worldScale, tileSize, tileSize, nrTilesetCols, nrTilesetRows, nrWorldCols, nrWorldRows);
		pGameScene_Level1->InitMusic("DiggerMusic.mp3");
	}

	//game level 2 scene
	Shining::Scene* pGameScene_Level2{ sceneManager.CreateScene("Game_Level2") };
	{
		pGameScene_Level2->Add(pFireball);
		pGameScene_Level2->Add(pPlayerCharacter);
		pGameScene_Level2->Add(pScoreboard);
		pGameScene_Level2->Add(pLivesCounter);
		pGameScene_Level2->Add(pLeftWall);
		pGameScene_Level2->Add(pRightWall);
		pGameScene_Level2->Add(pBottomWall);
		pGameScene_Level2->Add(pTopWall);
		//GEMS
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
		
		//GOLD BAGS
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 8 * scaledTileSize, 0 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 10 * scaledTileSize, 0 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 0 * scaledTileSize, 3 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 3 * scaledTileSize, 3 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 7 * scaledTileSize, 5 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 1 * scaledTileSize, 7 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level2, pPlayerHealth, 2 * scaledTileSize, 7 * scaledTileSize);
		//ENEMY
		AddEnemyToScene(pGameScene_Level2, pLevelChangeObserver, pScoreObserver, 14 * scaledTileSize, 0 * scaledTileSize);

		pLevelChangeObserver->AddGemGoal(41);
		pLevelChangeObserver->AddEnemyKillsGoal(1);

		pGameScene_Level2->InitWorld("Tileset.png", "Level_2.csv", worldScale, tileSize, tileSize, nrTilesetCols, nrTilesetRows, nrWorldCols, nrWorldRows);
		pGameScene_Level2->InitMusic("DiggerMusic.mp3");
	}

	//game level 3 scene
	Shining::Scene* pGameScene_Level3{ sceneManager.CreateScene("Game_Level3") };
	{
		pGameScene_Level3->Add(pFireball);
		pGameScene_Level3->Add(pPlayerCharacter);
		pGameScene_Level3->Add(pScoreboard);
		pGameScene_Level3->Add(pLivesCounter);
		pGameScene_Level3->Add(pLeftWall);
		pGameScene_Level3->Add(pRightWall);
		pGameScene_Level3->Add(pBottomWall);
		pGameScene_Level3->Add(pTopWall);
		//GEMS
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
		AddGemToScene(pGameScene_Level3, 5 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 9 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 13 * scaledTileSize, 9 * scaledTileSize);
		AddGemToScene(pGameScene_Level3, 14 * scaledTileSize, 9 * scaledTileSize);

		
		//GOLD BAGS
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 5 * scaledTileSize, 0 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 7 * scaledTileSize, 0 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 9 * scaledTileSize, 0 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 12 * scaledTileSize, 1 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 13 * scaledTileSize, 1 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 1 * scaledTileSize, 3 * scaledTileSize);
		AddGoldBagToScene(pGameScene_Level3, pPlayerHealth, 2 * scaledTileSize, 3 * scaledTileSize);

		//ENEMY
		AddEnemyToScene(pGameScene_Level3, pLevelChangeObserver, pScoreObserver, 9 * scaledTileSize, 5 * scaledTileSize);

		pLevelChangeObserver->AddEnemyKillsGoal(1);
		pLevelChangeObserver->AddGemGoal(51);

		pGameScene_Level3->InitWorld("Tileset.png", "Level_3.csv", worldScale, tileSize, tileSize, nrTilesetCols, nrTilesetRows, nrWorldCols, nrWorldRows);
		pGameScene_Level3->InitMusic("DiggerMusic.mp3");
	}

	//game over screen
	Shining::Scene* pGameOverScreen{ sceneManager.CreateScene("GameOver") };
	{		
		pGameOverScreen->Add(pScoreboard);
		const int textPosX{ 190 };

		Shining::GameObject* const pBigTextObject{ new Shining::GameObject(textPosX, windowHeight / 2) };
		const int bigTextSize{ 24 };
		Shining::TextComponent* const pBigText{ new Shining::TextComponent("Game over", "Retro Gaming.ttf", SDL_Color{210, 140, 140},bigTextSize) };
		pBigTextObject->AddComponent(pBigText);

		const int offsetY{ 50 };
		Shining::GameObject* const pSmallTextObject{ new Shining::GameObject(textPosX, windowHeight / 2 + offsetY) };
		const int smallTextSize{ 18 };
		Shining::TextComponent* const pSmallText{ new Shining::TextComponent("Thanks for playing!", "Retro Gaming.ttf", SDL_Color{210, 140, 140},smallTextSize) };
		pSmallTextObject->AddComponent(pSmallText);

		pGameOverScreen->Add(pBigTextObject);
		pGameOverScreen->Add(pSmallTextObject);
	}
	
	//setup input and commands
	//menu screen input
	{
		//create the commands
		Shining::InputContext* pMenuInput{ new Shining::InputContext() };
		StartGameCommand* const pStartGame{ new StartGameCommand() };
		//add them to the input context
		pMenuInput->AddCommand(pStartGame, SDLK_SPACE, Shining::ControllerInput::ButtonA);
		pMenuInput->AddCommand(pStartGame, SDLK_LEFT, Shining::ControllerInput::LeftStickLeft);
		pMenuInput->AddCommand(pStartGame, SDLK_RIGHT, Shining::ControllerInput::LeftStickRight);
		pMenuInput->AddCommand(pStartGame, SDLK_UP, Shining::ControllerInput::LeftStickUp);
		pMenuInput->AddCommand(pStartGame, SDLK_DOWN, Shining::ControllerInput::LeftStickDown);
		//set this context to the start menu
		pMenuScene->InitInputContext(pMenuInput);
	}

	//game input
	{	
		const float playerMoveSpeed{ 100.f };
		engine.SetPlayer(pPlayerCharacter); //this character controlled by both controller and keyboard
		//create the commands
		MoveRightCommand* const pMoveRight{ new MoveRightCommand(playerMoveSpeed) };
		MoveLeftCommand* const pMoveLeft{ new MoveLeftCommand(playerMoveSpeed) };
		MoveUpCommand* const pMoveUp{ new MoveUpCommand(playerMoveSpeed) };
		MoveDownCommand* const pMoveDown{ new MoveDownCommand(playerMoveSpeed) };
		StartIdleCommand* const pStartIdle{ new StartIdleCommand() };
		ShootCommand* const pShoot{ new ShootCommand() };
		//add them to the input context
		Shining::InputContext* pGameInput{ new Shining::InputContext() };
		pGameInput->AddCommand(pMoveRight, SDLK_RIGHT, Shining::ControllerInput::LeftStickRight);
		pGameInput->AddCommand(pMoveLeft, SDLK_LEFT, Shining::ControllerInput::LeftStickLeft);
		pGameInput->AddCommand(pMoveUp, SDLK_UP, Shining::ControllerInput::LeftStickUp);
		pGameInput->AddCommand(pMoveDown, SDLK_DOWN, Shining::ControllerInput::LeftStickDown);
		pGameInput->AddCommand(pShoot, SDLK_SPACE, Shining::ControllerInput::ButtonA);
		pGameInput->SetNoInputCommand(pStartIdle);
		//set this context for the game scenes
		pGameScene_Level1->InitInputContext(pGameInput);
		pGameScene_Level2->InitInputContext(pGameInput);
		pGameScene_Level3->InitInputContext(pGameInput);
	}

	sceneManager.SetScene(pMenuScene);
	Shining::AudioPlayer::GetInstance().SetMusicVolume(50);
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
	Shining::CollisionBehavior* const pPickupCollision{ new PickupCollision(true) };
	pGemCollision->SetBehavior(pPickupCollision);
	pGem->AddComponent(pGemCollision);

	pSceneToAddTo->Add(pGem);
}

void AddGoldBagToScene(Shining::Scene* const pSceneToAddTo, Shining::HealthComponent* const pPlayerHealth, const float xPos, const float yPos)
{
	const int bagOffsetX{ 5 }; //better center the bag on the tile
	const int bagOffsetY{ 2 }; //make sure the bag doesn't stick to a ceiling
	//bag
	//render
	Shining::GameObject* const pBag{ new Shining::GameObject(xPos + bagOffsetX, yPos + bagOffsetY) };
	Shining::RenderComponent* const pBagRender{ new Shining::RenderComponent("GoldBag.png", 2) };
	pBag->AddComponent(pBagRender);

	//state
	BagIdleState* const pBagIdleState{ new BagIdleState{} };
	BagWarningState* const pBagWarningState{ new BagWarningState() };
	BagFallingState* const pBagFallingState{ new BagFallingState() };
	Shining::StateComponent* const pBagStates{ new Shining::StateComponent(pBagIdleState, pBag) };
	pBagStates->AddState(pBagWarningState);
	pBagStates->AddState(pBagFallingState);
	pBag->AddComponent(pBagStates);

	//physics
	Shining::PhysicsComponent* const pBagPhysics{ new Shining::PhysicsComponent(pBag, false) };
	pBag->AddComponent(pBagPhysics);

	//collision
	Shining::CollisionComponent* const pBagCollision{ new Shining::CollisionComponent(pBag, pBagRender, int(CollisionTags::goldBag), true, false) };
	Shining::CollisionBehavior* const pBagCollisionBehavior{ new BagCollision(pPlayerHealth) };
	pBagCollision->SetBehavior(pBagCollisionBehavior);
	pBagCollision->AddTargetTag(int(CollisionTags::player));
	pBagCollision->AddTargetTag(int(CollisionTags::wall));
	pBagCollision->AddTargetTag(int(CollisionTags::enemy));
	pBag->AddComponent(pBagCollision);

	//gold
	//render
	Shining::GameObject* const pGold{ new Shining::GameObject(-100,0) }; //object will be spawned at the position of the bag when it breaks
	Shining::RenderComponent* const pGoldRender(new Shining::RenderComponent("Gold.png", 2));
	pGold->AddComponent(pGoldRender);

	//collision
	Shining::CollisionComponent* const pGoldCollision{ new Shining::CollisionComponent(pGold, pGoldRender, int(CollisionTags::gold), false, false) };
	Shining::CollisionBehavior* const pGoldCollisionBehavior{ new PickupCollision(false) };
	pGoldCollision->SetBehavior(pGoldCollisionBehavior);
	pGoldCollision->AddTargetTag(int(CollisionTags::player));
	pGold->AddComponent(pGoldCollision);

	//gold spawner added to bag
	Shining::SpawnComponent* const pGoldSpawn{ new Shining::SpawnComponent(pGold, false) };
	pBag->AddComponent(pGoldSpawn); //add to the bag, so the bag can spawn the gold
	pSceneToAddTo->Add(pBag);
	pSceneToAddTo->Add(pGold);
}

void AddEnemyToScene(Shining::Scene* const pSceneToAddTo, LevelChangeObserver* const pLevelChangeObs, ScoreObserver* const pScoreObs, const float xPos, const float yPos)
{
	Shining::GameObject* const pEnemy{ new Shining::GameObject(xPos, yPos) };
	//render
	Shining::RenderComponent* const pRender{ new Shining::RenderComponent("Enemy.png", 2, 70, 1, 3) };
	pEnemy->AddComponent(pRender);
	//collision
	Shining::CollisionComponent* const pCollision{ new Shining::CollisionComponent(pEnemy, pRender, int(CollisionTags::enemy), true, false) };
	pCollision->AddTargetTag(int(CollisionTags::player));
	Shining::CollisionBehavior* const pBehavior{ new EnemyCollision() };
	pCollision->SetBehavior(pBehavior);
	pEnemy->AddComponent(pCollision);
	//physics
	Shining::PhysicsComponent* const pPhysics{ new Shining::PhysicsComponent(pEnemy, false) };
	pEnemy->AddComponent(pPhysics);

	pEnemy->AddObserver(pLevelChangeObs);
	pEnemy->AddObserver(pScoreObs);

	pSceneToAddTo->Add(pEnemy);

}