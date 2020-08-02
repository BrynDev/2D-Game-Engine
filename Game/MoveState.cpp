#include "MoveState.h"
#include "IdleState.h"


MoveState::MoveState()
	:State()
{
}

void MoveState::Update(Shining::GameObject* const pOwner, const float timeStep) noexcept
{
	Shining::PhysicsComponent* pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->MoveOwner(timeStep);
	/*if (pPhysics->IsNotMoving())
	{
		pOwner->GetComponent<Shining::StateComponent>()->ChangeState<IdleState>();
	}*/
}

void MoveState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::RenderComponent* pSprite{ pOwner->GetComponent<Shining::RenderComponent>() };
	if (pSprite != nullptr)
	{
		//pSprite->SetFlipFlag();
	}
}

void MoveState::OnExit(Shining::GameObject* const pOwner) noexcept
{
	Shining::PhysicsComponent* pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	if (pPhysics != nullptr)
	{
		//pPhysics->SetDirection(0, 0);
		//pPhysics->SetSpeed(0, 0);
	}
}