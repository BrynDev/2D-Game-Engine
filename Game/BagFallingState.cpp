#include "BagFallingState.h"
#include "ShiningEnginePCH.h"
#include "BagIdleState.h"

BagFallingState::BagFallingState()
	:State()
	, m_FallDelayTimerMs{0}
	, m_IsFalling{false}
	, m_HasHitBottomWall{false}
{

}

void BagFallingState::Update(Shining::GameObject* const pOwner, const float timeStep) noexcept
{
	const int fallDelayMs{ 1000 };
	if (!m_IsFalling)
	{
		m_FallDelayTimerMs += int(timeStep);
		if (m_FallDelayTimerMs >= fallDelayMs)
		{
			//start falling
			m_IsFalling = true;			

			Shining::AudioPlayer::GetInstance().PlaySoundEffect("BagFalling.wav");
			Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
			pPhysics->SetIsMoving(true);
			return;
		}
		return;
	}
	
	Shining::CollisionComponent* const pCollision{ pOwner->GetComponent<Shining::CollisionComponent>() };
	if (!pCollision->HasHitWorld() && !m_HasHitBottomWall) //check if bag has hit a floor
	{
		return;
	}
	//bag has hit floor	
	Shining::AudioPlayer::GetInstance().StopAllEffects(); //stop the falling sound
	//break bag
	pOwner->SetActive(false);
	Shining::SpawnComponent* const pGoldSpawn{ pOwner->GetComponent<Shining::SpawnComponent>() };
	const glm::vec2& ownerPos{ pOwner->GetPosition() };
	pGoldSpawn->SpawnObject(ownerPos.x, ownerPos.y);
}

void BagFallingState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::AudioPlayer::GetInstance().PlaySoundEffect("BagFallWarning.wav");
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };

	pPhysics->SetDirection(0, 1);
	const float fallSpeed{ 200.f };
	pPhysics->SetSpeed(0, fallSpeed);
}

void BagFallingState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	m_FallDelayTimerMs = 0;
	m_IsFalling = false;
	m_HasHitBottomWall = false;
}

void BagFallingState::HitBottomWall() noexcept
{
	m_HasHitBottomWall = true;
}