#pragma once
#include "CollisionBehavior.h"

class EnemyCollision final : public Shining::CollisionBehavior
{
public:
	explicit EnemyCollision() = default;
	virtual ~EnemyCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept override;
	virtual void ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept override;
private:
};

