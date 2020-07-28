#pragma once
#include "Command.h"

class MoveCommand final : public Shining::Command
{
public:
	MoveCommand();
	virtual ~MoveCommand() = default;

	virtual void Execute( Shining::GameObject* const pTargetObject) const noexcept override;
private:
};

