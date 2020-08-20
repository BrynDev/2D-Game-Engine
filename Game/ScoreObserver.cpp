#include "ScoreObserver.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

ScoreObserver::ScoreObserver(Shining::GameObject* pScoreboard)
	:Observer()
	, m_pScoreboard{pScoreboard}
	, m_Score{0}
	, m_GemPickupStreak{0}
	, m_GemPickupStreakMax{8}
{
}

void ScoreObserver::Notify(Shining::GameObject* const /*pSubject*/, const int eventID, void* /*pData*/) noexcept
{
	switch (eventID)
	{
	case int(ObservedEvents::gemPickup):
		m_Score += 25;
		++m_GemPickupStreak;
		if (m_GemPickupStreak >= m_GemPickupStreakMax)
		{
			m_Score += 250;
			m_GemPickupStreak = 0;
		}
		break;
	case int(ObservedEvents::goldPickup):
		m_GemPickupStreak = 0;
		m_Score += 500;
		break;
		case int(ObservedEvents::enemyKill):
		m_Score += 250;
		break;
	default:
		break;
	}

	m_pScoreboard->GetComponent<Shining::TextComponent>()->SetText(std::to_string(m_Score));
}