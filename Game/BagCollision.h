#pragma once
#include "CollisionBehavior.h"

class BagCollision final : public Shining::CollisionBehavior
{
public:
	explicit BagCollision() = default;
	virtual ~BagCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept override;
	virtual void ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept override;
private:
};

