#pragma once
#include "Command.h"

class MoveLeftCommand final : public Shining::Command
{
public:
	MoveLeftCommand(const float moveSpeed);
	virtual ~MoveLeftCommand() = default;

	virtual void Execute(Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
private:
	const float m_MoveSpeed;
};

