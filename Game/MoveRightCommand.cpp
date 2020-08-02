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
	pPhysics->SetSpeed(150, 0);
	pPhysics->SetDirection(1, 0);
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();
}

void MoveRightCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused
}