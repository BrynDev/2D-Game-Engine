#include "BagFallingState.h"
#include "ShiningEnginePCH.h"
#include "BagIdleState.h"

BagFallingState::BagFallingState()
	:State()
	, m_FallDelayTimerMs{0}
	, m_IsFalling{false}
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

			Shining::AudioPlayer::GetInstance().PlaySoundEffect("BagFallingSound.wav");
			Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
			pPhysics->SetIsMoving(true);
			return;
		}
		return;
	}
}

void BagFallingState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::AudioPlayer::GetInstance().PlaySoundEffect("BagFallWarningSound.wav");
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };

	pPhysics->SetDirection(0, 1);
	const float fallSpeed{ 200.f };
	pPhysics->SetSpeed(0, fallSpeed);
}

void BagFallingState::OnExit(Shining::GameObject* const pOwner) noexcept
{
	m_FallDelayTimerMs = 0;
	m_IsFalling = false;

	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false);
}