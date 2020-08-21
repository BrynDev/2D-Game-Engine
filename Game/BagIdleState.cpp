#include "BagIdleState.h"
#include "ShiningEnginePCH.h"
#include "BagFallingState.h"

BagIdleState::BagIdleState()
	:State()
{

}

void BagIdleState::Update(Shining::GameObject* const pOwner, const float /*timeStep*/) noexcept
{
	Shining::CollisionComponent* const pCollision{ pOwner->GetComponent<Shining::CollisionComponent>() };

	if (pCollision->HasHitWorld())
	{
		return;
	}
	
	Shining::StateComponent* pState{ pOwner->GetComponent<Shining::StateComponent>() };
	pState->ChangeState<BagFallingState>();
	
}

void BagIdleState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false);
}

void BagIdleState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{

}