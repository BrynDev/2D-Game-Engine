#pragma once
#include "CollisionBehavior.h"

namespace Shining //class forward declaration of namespace class
{
	class HealthComponent;
}

class BagCollision final : public Shining::CollisionBehavior
{
public:
	explicit BagCollision(Shining::HealthComponent* const pPlayerHealth);
	virtual ~BagCollision() = default;

	virtual void ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept override;
	virtual void ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept override;
private:
	Shining::HealthComponent* const m_pPlayerHealth;
};

