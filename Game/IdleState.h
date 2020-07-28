#pragma once

#include "State.h"

class IdleState final : public Shining::State
{
public:
	IdleState();
	virtual ~IdleState() = default;

	virtual void Update(Shining::GameObject* const pOwner, const float timeStep) noexcept override;
	virtual void OnEntry(Shining::GameObject* const pOwner) noexcept override;
	virtual void OnExit(Shining::GameObject* const pOwner) noexcept override;
private:
};

