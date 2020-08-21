#pragma once
#include "CollisionBehavior.h"

class FireballCollision final : public Shining::CollisionBehavior
{
public:
	explicit FireballCollision() = default;
	virtual ~FireballCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept override;
private:
};

