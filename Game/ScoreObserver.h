#pragma once
#include "Observer.h"

class ScoreObserver final: public Shining::Observer 
{
public:
	ScoreObserver(Shining::GameObject* pScoreboard);
	virtual ~ScoreObserver() = default;

	virtual void Notify(Shining::GameObject* const pSubject, const int eventID, void* pData) noexcept override;
private:
	Shining::GameObject* m_pScoreboard;
	int m_Score;
	int m_GemPickupStreak;
	const int m_GemPickupStreakMax;
};

