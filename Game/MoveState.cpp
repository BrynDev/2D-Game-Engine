#include "MoveState.h"
#include "IdleState.h"
#include "ShiningEnginePCH.h"


MoveState::MoveState()
	:State()
{
}

void MoveState::Update(Shining::GameObject* const /*pOwner*/, const float /*timeStep*/) noexcept
{
	//empty
}

void MoveState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	//empty
	Shining::PhysicsComponent* pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(true);
}

void MoveState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	//empty
}