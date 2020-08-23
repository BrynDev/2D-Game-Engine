#pragma once

namespace Shining
{
	class GameObject;

	class HitBehavior
	{
	public:
		explicit HitBehavior() = default;
		virtual ~HitBehavior() = default;

		virtual void OnHit(Shining::GameObject* const pHitObject, const int damageTaken) const noexcept = 0;
		virtual void OnDeath(Shining::GameObject* const pDeadObject) const noexcept = 0;
		void IncreaseInstanceCount() noexcept;
		bool DecreaseInstanceCount() noexcept; //returns true if the instance count is 0, the owner object then deletes this
	private:
		int m_InstanceCount;
	};
}

