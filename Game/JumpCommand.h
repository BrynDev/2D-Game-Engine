#pragma once
#include "Command.h"

class JumpCommand final : public Shining::Command
{
public:
	JumpCommand() = default;
	virtual ~JumpCommand() = default;

	virtual void Execute(const Shining::GameObject* pTargetObject) const override;
private:
};

