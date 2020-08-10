#pragma once
#include "CollisionBehavior.h"

class PickupCollision final : public Shining::CollisionBehavior
{
public:
	PickupCollision() = default;
	virtual ~PickupCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept override;
private:
};

