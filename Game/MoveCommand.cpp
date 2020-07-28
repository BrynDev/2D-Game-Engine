#include "MoveCommand.h"
#include "StateComponent.h"
#include "MoveState.h"

MoveCommand::MoveCommand()
	:Command()
{
}

void MoveCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();
}