#pragma once
#include "State.h"

class BagFallingState final : public Shining::State
{
public:
	BagFallingState();
	virtual ~BagFallingState() = default;

	virtual void Update(Shining::GameObject* const pOwner, const float timeStep) noexcept override;
	virtual void OnEntry(Shining::GameObject* const pOwner) noexcept override;
	virtual void OnExit(Shining::GameObject* const pOwner) noexcept override;

	void HitBottomWall() noexcept;
private:
	int m_FallDelayTimerMs;
	bool m_IsFalling;
	bool m_HasHitBottomWall;
	
};

