#pragma once
#include "Command.h"

class MoveRightCommand final : public Shining::Command
{
public:
	MoveRightCommand(const float moveSpeed);
	virtual ~MoveRightCommand() = default;

	virtual void Execute( Shining::GameObject* const pTargetObject) const noexcept override;
	virtual void OnRelease(Shining::GameObject* const pTargetObject) const noexcept override;
private:
	const float m_MoveSpeed;
};

