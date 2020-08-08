#pragma once
#include "Command.h"

class MoveDownCommand final : public Shining::Command
{
public:
	MoveDownCommand();
	virtual ~MoveDownCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
};

