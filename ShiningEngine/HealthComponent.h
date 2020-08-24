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

		void GetHit(const int damageTaken) noexcept; //calls HitBehavior->OnHit(), which will determine the next action
		void TakeDamage(const int damageTaken) noexcept; //unconditionally deals damage to component
		const int GetCurrentHealth() const noexcept; 
		void SetHitBehavior(HitBehavior* const pHitBehavior) noexcept;
		
	private:
		static NullHit m_NullHit;
		HitBehavior* m_pHitBehavior;
		GameObject* const m_pOwner;
		const int m_MaxHealth;
		int m_CurrentHealth;
		int m_NextHealth;
		bool m_NeedsSwap;
	};

}

