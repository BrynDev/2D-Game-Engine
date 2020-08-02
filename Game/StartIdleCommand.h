#pragma once
#include "Command.h"

class StartIdleCommand final : public Shining::Command
{
public:
	StartIdleCommand();
	virtual ~StartIdleCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
private:
};

