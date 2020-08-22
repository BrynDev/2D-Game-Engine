#pragma once
#include "State.h"

class ShotCooldownState final : public Shining::State
{
public:
	explicit ShotCooldownState();
	virtual ~ShotCooldownState() = default;

	virtual void Update(Shining::GameObject* const pOwner, const float timeStep) noexcept override;
	virtual void OnEntry(Shining::GameObject* const pOwner) noexcept override;
	virtual void OnExit(Shining::GameObject* const pOwner) noexcept override;
private:
	const int m_CooldownMaxMs;
	int m_TimerMs;
};

