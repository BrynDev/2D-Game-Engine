#pragma once
//#include "Command.h"
#include "ShiningEnginePCH.h"

class StartGameKeyboardCommand final : public Shining::Command
{
public:
	explicit StartGameKeyboardCommand(Shining::ShiningEngine* const pEngine, Shining::GameObject* const pPlayer1,  Shining::GameObject* const pPlayer2);
	virtual ~StartGameKeyboardCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
private:
	Shining::ShiningEngine* const m_pEngine;
	Shining::GameObject* const m_pPlayer1;
	Shining::GameObject* const m_pPlayer2;
};


