#pragma once
#include "Component.h"
#include "NullHit.h"

namespace Shining
{
	class HitBehavior;
	class GameObject;

	class HealthComponent final : public Component
	{
	public:
		explicit HealthComponent(GameObject* const pOwner, const int maxHealth);
		explicit HealthComponent(GameObject* const pOwner, const int maxHealth, const int currentHealth);
		virtual ~HealthComponent();

		virtual void Update(const float timeStep) override;
		virtual void Render(const glm::vec2 & pos) const override;
		virtual void SwapBuffer() noexcept override;

		void SetHitBehavior(HitBehavior* const pHitBehavior) noexcept;
		void TakeDamage(const int damageTaken) noexcept;
		const int GetCurrentHealth() const noexcept;

	private:
		static NullHit m_NullHit;
		HitBehavior* m_pHitBehavior;
		GameObject* const m_pOwner;
		const int m_MaxHealth;
		int m_CurrentHealth;
		int m_NextHealth;
		bool m_IsDead;
		bool m_NeedsSwap;
	};

}

