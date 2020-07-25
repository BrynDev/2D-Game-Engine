#include "MoveState.h"


MoveState::MoveState()
	:State()
{
}

void MoveState::Update(Shining::GameObject* const /*pOwner*/, const float /*timeStep*/) noexcept
{
	//pOwner->GetComponent
}

void MoveState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::RenderComponent* pSprite{ pOwner->GetComponent<Shining::RenderComponent>() };
	if (pSprite != nullptr)
	{
		//pSprite->SetFlipFlag();
	}
}

void MoveState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{

}