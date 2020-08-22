#pragma once
#include "CollisionBehavior.h"


class PlayerCollision final: public Shining::CollisionBehavior
{
public:
	explicit PlayerCollision() = default;
	virtual ~PlayerCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept override;
	virtual void ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept override;
private:
};

