#pragma once
#include "Command.h"

class StartGameCommand final : public Shining::Command
{
public:
	StartGameCommand();
	virtual ~StartGameCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
private:
};

