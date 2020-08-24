#include "ShiningEnginePCH.h"
#include "HealthComponent.h"
#include "HitBehavior.h"

Shining::NullHit Shining::HealthComponent::m_NullHit;

Shining::HealthComponent::HealthComponent(GameObject* const pOwner, const int maxHealth)
	:HealthComponent(pOwner, maxHealth, maxHealth)
{
}

Shining::HealthComponent::HealthComponent(GameObject* const pOwner, const int maxHealth, const int currentHealth)
	:Component()
	, m_pHitBehavior{&m_NullHit}
	, m_pOwner{pOwner}
	, m_MaxHealth{maxHealth}
	, m_CurrentHealth{currentHealth}
	, m_NextHealth{m_CurrentHealth}
	, m_NeedsSwap{false}
{
}

Shining::HealthComponent::~HealthComponent()
{
	if (m_pHitBehavior != &m_NullHit) //don't delete the null object
	{
		if (m_pHitBehavior->DecreaseInstanceCount())
		{
			delete m_pHitBehavior;
		}
	}
}

void Shining::HealthComponent::Update(const float /*timeStep*/)
{
	//empty
}

void Shining::HealthComponent::Render(const glm::vec2& /*pos*/) const
{
	//empty
}

void Shining::HealthComponent::SwapBuffer() noexcept
{
	if (!m_NeedsSwap)
	{
		return;
	}

	const int damageTaken{ m_CurrentHealth - m_NextHealth };
	m_CurrentHealth = m_NextHealth; 

	if (m_CurrentHealth <= 0)
	{
		m_pHitBehavior->OnDeath(m_pOwner);
	}

	m_NeedsSwap = false;
}


void Shining::HealthComponent::GetHit(const int damageTaken) noexcept
{
	m_pHitBehavior->OnHit(m_pOwner, damageTaken);
}

void Shining::HealthComponent::TakeDamage(const int damageTaken) noexcept
{
	m_NextHealth = m_CurrentHealth - damageTaken;
	m_NeedsSwap = true;
}

const int Shining::HealthComponent::GetCurrentHealth() const noexcept
{
	return m_CurrentHealth;
}

void Shining::HealthComponent::SetHitBehavior(HitBehavior* const pHitBehavior) noexcept
{
	if (pHitBehavior == nullptr)
	{
		return;
	}

	if (m_pHitBehavior != &m_NullHit)
	{
		if (m_pHitBehavior->DecreaseInstanceCount()) //if this behavior isnt owned by anything anymore, delete it
		{
			delete m_pHitBehavior;
		}	
	}

	pHitBehavior->IncreaseInstanceCount();
	m_pHitBehavior = pHitBehavior;
}