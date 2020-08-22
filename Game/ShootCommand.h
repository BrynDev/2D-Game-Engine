#pragma once
#include "Command.h"

class ShootCommand final : public Shining::Command
{
public:
	explicit ShootCommand() = default;
	virtual ~ShootCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
private:
};

