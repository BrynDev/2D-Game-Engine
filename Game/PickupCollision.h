#pragma once
#include "CollisionBehavior.h"

class PickupCollision final : public Shining::CollisionBehavior
{
public:
	explicit PickupCollision(const bool isGem);
	virtual ~PickupCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept override;
private:
	const bool m_IsGem; //if false, this is gold
};

