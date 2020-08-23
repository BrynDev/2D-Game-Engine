#pragma once
#include "HitBehavior.h"

namespace Shining
{
	class NullHit final : public HitBehavior
	{
	public:
		explicit NullHit() = default;
		virtual ~NullHit() = default;

		virtual void OnHit(GameObject* const pHitObject, const int damageTaken) const noexcept override;
		virtual void OnDeath(GameObject* const pDeadObject) const noexcept override;
	private:
	};
}


