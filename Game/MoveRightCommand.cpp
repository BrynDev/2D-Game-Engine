#include "MoveRightCommand.h"
#include "ShiningEnginePCH.h"
#include "MoveState.h"
#include "IdleState.h"


MoveRightCommand::MoveRightCommand()
	:Command()
{
}

void MoveRightCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::PhysicsComponent* pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
	//pPhysics->SetSpeed(150, 0);
	pPhysics->SetDirection(1, 0);
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();

	Shining::RenderComponent* pRender{ pTargetObject->GetComponent<Shining::RenderComponent>() };
	pRender->SetFlipFlag(Shining::RenderFlipFlag::none);
	pRender->SetRotationAngle(0.f);
}

void MoveRightCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused
}