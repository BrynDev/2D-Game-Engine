#include "MoveRightCommand.h"
#include "MoveState.h"
#include "IdleState.h"
#include "DyingState.h"
#include "ShiningEnginePCH.h"

MoveRightCommand::MoveRightCommand(const float moveSpeed)
	:Command()
	, m_MoveSpeed{moveSpeed}
{
}

void MoveRightCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::StateComponent* const pState{ pTargetObject->GetComponent<Shining::StateComponent>() };
	if (!pState->IsCurrentState<DyingState>()) //block inputs if the player is dying
	{
		Shining::PhysicsComponent* pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
		if (pPhysics == nullptr)
		{
			return;
		}

		pPhysics->SetSpeed(m_MoveSpeed, 0);
		pPhysics->SetDirection(1, 0);
		pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();

		Shining::RenderComponent* pRender{ pTargetObject->GetComponent<Shining::RenderComponent>() };
		pRender->SetFlipFlag(Shining::RenderFlipFlag::none);
		pRender->SetRotationAngle(0.f);
	}
	
}

void MoveRightCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused
}