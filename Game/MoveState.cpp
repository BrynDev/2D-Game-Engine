#include "MoveState.h"


MoveState::MoveState()
	:State()
{
}

void MoveState::Update(Shining::GameObject* const pOwner, const float timeStep) noexcept
{
	pOwner->GetComponent<Shining::PhysicsComponent>()->MoveOwner(timeStep);
}

void MoveState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::RenderComponent* pSprite{ pOwner->GetComponent<Shining::RenderComponent>() };
	if (pSprite != nullptr)
	{
		//pSprite->SetFlipFlag();
	}

	pOwner->GetComponent<Shining::PhysicsComponent>()->SetDirection(1, 0);
	pOwner->GetComponent<Shining::PhysicsComponent>()->SetSpeed(10, 0);
}

void MoveState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{

}