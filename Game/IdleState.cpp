#include "IdleState.h"
#include "ShiningEnginePCH.h"


void IdleState::Update(Shining::GameObject* const /*pOwner*/, const float /*timeStep*/) noexcept
{
	//empty
}

void IdleState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false);
}

void IdleState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	//empty
}