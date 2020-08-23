#include "BagFallingState.h"
#include "ShiningEnginePCH.h"
#include "BagIdleState.h"

void BagFallingState::Update(Shining::GameObject* const /*pOwner*/, const float /*timeStep*/) noexcept
{
	//empty
}

void BagFallingState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::AudioPlayer::GetInstance().PlaySoundEffect("BagFallingSound.wav");

	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetDirection(0, 1);
	const float fallSpeed{ 200.f };
	pPhysics->SetSpeed(0, fallSpeed);
	pPhysics->SetIsMoving(true);
}

void BagFallingState::OnExit(Shining::GameObject* const pOwner) noexcept
{
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false);
}