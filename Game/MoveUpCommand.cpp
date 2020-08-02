#include "MoveUpCommand.h"
#include "ShiningEnginePCH.h"
#include "MoveState.h"
#include "IdleState.h"


MoveUpCommand::MoveUpCommand()
	:Command()
{
}

void MoveUpCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::PhysicsComponent* pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetSpeed(0, 150);
	pPhysics->SetDirection(0, -1);
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();
}

void MoveUpCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
}