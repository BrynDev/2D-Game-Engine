#include "MoveDownCommand.h"
#include "ShiningEnginePCH.h"
#include "MoveState.h"
#include "IdleState.h"

MoveDownCommand::MoveDownCommand()
	:Command()
{

}

void MoveDownCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::PhysicsComponent* pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetSpeed(0, 150);
	pPhysics->SetDirection(0, 1);
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();
}

void MoveDownCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused
}