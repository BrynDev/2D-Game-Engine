#pragma once
#include "HitBehavior.h"

class PlayerHit final : public Shining::HitBehavior
{
public:
	explicit PlayerHit() = default;
	virtual ~PlayerHit() = default;

	virtual void OnHit(Shining::GameObject* const pHitObject, const int damageTaken) const noexcept override;
	virtual void OnDeath(Shining::GameObject* const pDeadObject) const noexcept override;
private:
};

