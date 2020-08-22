#include "BagIdleState.h"
#include "ShiningEnginePCH.h"
#include "BagFallingState.h"

BagIdleState::BagIdleState()
	:State()
	, m_CanFall{false}
{

}

void BagIdleState::Update(Shining::GameObject* const pOwner, const float /*timeStep*/) noexcept
{
	if (m_CanFall)
	{
		Shining::StateComponent* pState{ pOwner->GetComponent<Shining::StateComponent>() };
		pState->ChangeState<BagFallingState>();
	}

	m_CanFall = true; //bag will attempt to fall, of colliding with world this will be set to false
}

void BagIdleState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false);
}

void BagIdleState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	m_CanFall = false;
}

void BagIdleState::DenyFall() noexcept
{
	m_CanFall = false;
}