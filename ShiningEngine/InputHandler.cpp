#include "ShiningEnginePCH.h"
#include "InputHandler.h"
#include "InputManager.h"
#include "Command.h"

Shining::InputHandler::InputHandler(Shining::GameObject* const pObjectToControl)
	:m_pCommands{}
	, m_pObjectToControl{pObjectToControl}
{
	InputManager::GetInstance().RegisterInputHandler(this);
}

Shining::InputHandler::~InputHandler()
{
	for (const Shining::Command* pCommand : m_pCommands)
	{
		delete pCommand;
	}
}

void Shining::InputHandler::HandleInput(const unsigned int keyDownScanCode) const noexcept
{
	for (const Shining::Command* pCommand : m_pCommands)
	{
		if (pCommand->GetKeyScanCode() == keyDownScanCode)
		{
			pCommand->Execute(m_pObjectToControl);
			break;
		}
	}
}

void Shining::InputHandler::AddCommand(const Shining::Command* pCommandToAdd)
{
	m_pCommands.push_back(pCommandToAdd);
}
