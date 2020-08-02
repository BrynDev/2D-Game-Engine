#include "StartIdleCommand.h"
#include "ShiningEnginePCH.h"
#include "IdleState.h"

StartIdleCommand::StartIdleCommand()
	:Command()
{
}

void StartIdleCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<IdleState>();
}

void StartIdleCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused function
}