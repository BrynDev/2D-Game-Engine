#include "ScoreObserver.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

ScoreObserver::ScoreObserver(Shining::TextComponent* const pScoreText)
	:Observer()
	, m_pScoreText{pScoreText}
	, m_Score{0}
	, m_ExtraLifeCount{0}
	, m_GemPickupStreak{0}
	, m_GemPickupStreakMax{8}
{
}

void ScoreObserver::Notify(Shining::GameObject* const pSubject, const int eventID, void* /*pData*/) noexcept
{
	bool scoreChanged{ false };
	int scoreIncrease{ 0 };
	switch (eventID)
	{
	case int(ObservedEvents::gemPickup):
		scoreIncrease += 25;
		++m_GemPickupStreak;
		if (m_GemPickupStreak >= m_GemPickupStreakMax)
		{
			scoreIncrease += 250;
			m_GemPickupStreak = 0;
		}
		scoreChanged = true;
		break;
	case int(ObservedEvents::goldPickup):
		m_GemPickupStreak = 0;
		scoreIncrease += 500;
		scoreChanged = true;
		break;
	case int(ObservedEvents::enemyKill):
		m_GemPickupStreak = 0;
		scoreIncrease += 250;
		scoreChanged = true;
		break;
	default:
		break;
	}

	
	if (scoreChanged)
	{
		m_Score += scoreIncrease;
		m_pScoreText->SetText(std::to_string(m_Score));
		

		m_ExtraLifeCount += scoreIncrease;
		const int scorePerLife{ 20000 }; //award an extra life every 20.000 points
		if (m_ExtraLifeCount >= scorePerLife)
		{
			m_ExtraLifeCount -= scorePerLife;
			pSubject->NotifyObservers(int(ObservedEvents::extraLifeEarned));
		}
	}
}