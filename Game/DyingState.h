#pragma once
#include "State.h"

class DyingState final : public Shining::State
{
public:
	explicit DyingState();
	virtual ~DyingState() = default;

	virtual void Update(Shining::GameObject* const pOwner, const float timeStep) noexcept override;
	virtual void OnEntry(Shining::GameObject* const pOwner) noexcept override;
	virtual void OnExit(Shining::GameObject* const pOwner) noexcept override;
private:
	int m_DyingTimer;
};

