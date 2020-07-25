#pragma once
#include "ShiningEnginePCH.h"

class MoveState : public Shining::State
{
public:
	MoveState();
	virtual ~MoveState() = default;
	virtual void Update(Shining::GameObject* const pOwner, const float timeStep) noexcept override;
	virtual void OnEntry(Shining::GameObject* const pOwner) noexcept override;
	virtual void OnExit(Shining::GameObject* const pOwner) noexcept override;
private:
};

