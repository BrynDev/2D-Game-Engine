#include "StartGameCommand.h"
#include "ShiningEnginePCH.h"

StartGameCommand::StartGameCommand()
	:Command()
{

}

void StartGameCommand::Execute(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	Shining::SceneManager::GetInstance().AdvanceScene();
}

void StartGameCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{

}