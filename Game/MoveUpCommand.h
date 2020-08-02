#pragma once
#include "Command.h"

class MoveUpCommand final : public Shining::Command
{
public:
	MoveUpCommand();
	virtual ~MoveUpCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
};

