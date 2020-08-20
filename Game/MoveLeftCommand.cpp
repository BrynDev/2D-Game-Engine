#include "MoveLeftCommand.h"
#include "MoveState.h"
#include "IdleState.h"
#include "ShiningEnginePCH.h"

MoveLeftCommand::MoveLeftCommand(const float moveSpeed)
	:Command()
	, m_MoveSpeed{moveSpeed}
{
}

void MoveLeftCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::PhysicsComponent* pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
	if (pPhysics == nullptr)
	{
		return;
	}

	pPhysics->SetSpeed(m_MoveSpeed, 0);
	pPhysics->SetDirection(-1, 0);
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();

	Shining::RenderComponent* pRender{ pTargetObject->GetComponent<Shining::RenderComponent>() };
	pRender->SetFlipFlag(Shining::RenderFlipFlag::horizontal);
	pRender->SetRotationAngle(0.f);
}

void MoveLeftCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused
}