#include "StartGameControllerCommand.h"

StartGameControllerCommand::StartGameControllerCommand(Shining::ShiningEngine* const pEngine, Shining::GameObject* const pPlayer1, Shining::GameObject* const pPlayer2)
	:Command()
	, m_pEngine{ pEngine }
	, m_pPlayer1{ pPlayer1 }
	, m_pPlayer2{ pPlayer2 }
{

}

void StartGameControllerCommand::Execute(Shining::GameObject* const /*pTargetObject*/) const noexcept
{	
	m_pEngine->SetControllerPlayer(m_pPlayer1);
	m_pEngine->SetKeyboardPlayer(m_pPlayer2);	

	Shining::SceneManager::GetInstance().AdvanceScene();
}

void StartGameControllerCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{

}