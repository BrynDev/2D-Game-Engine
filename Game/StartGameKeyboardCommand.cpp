#include "StartGameKeyboardCommand.h"
//#include "ShiningEnginePCH.h"

StartGameKeyboardCommand::StartGameKeyboardCommand(Shining::ShiningEngine* const pEngine, Shining::GameObject* const pPlayer1, Shining::GameObject* const pPlayer2)
	:Command()
	, m_pEngine{pEngine}
	, m_pPlayer1{pPlayer1}
	, m_pPlayer2{pPlayer2}
{

}

void StartGameKeyboardCommand::Execute(Shining::GameObject* const /*pTargetObject*/) const noexcept
{	
	m_pEngine->SetKeyboardPlayer(m_pPlayer1);
	m_pEngine->SetControllerPlayer(m_pPlayer2);

	Shining::SceneManager::GetInstance().AdvanceScene();
}

void StartGameKeyboardCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{

}