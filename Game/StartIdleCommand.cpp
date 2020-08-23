#include "StartIdleCommand.h"
#include "IdleState.h"
#include "ShiningEnginePCH.h"
#include "DyingState.h"

StartIdleCommand::StartIdleCommand()
	:Command()
{
}

void StartIdleCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::StateComponent* const pState{ pTargetObject->GetComponent<Shining::StateComponent>() };
	if (!pState->IsCurrentState<DyingState>()) //block inputs if the player is dying
	{
		pState->ChangeState<IdleState>();
	}	
}

void StartIdleCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//unused function
}