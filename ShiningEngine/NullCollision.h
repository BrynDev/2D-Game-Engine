#pragma once
#include "CollisionBehavior.h"

namespace Shining
{
	//this class does nothing, it's used as a default behavior in collision components to avoid nullptr checks or crashes in case of invalid collision resolution
	class NullCollision final : public CollisionBehavior
	{
	public:
		NullCollision();
		virtual ~NullCollision() = default;

		virtual void ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept override;
		virtual void ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept override;
	private:
	};

}

