#pragma once
#include "Observer.h"

class ScoreObserver final: public Shining::Observer 
{
public:
	ScoreObserver(Shining::GameObject* pObjectToModify);
	virtual ~ScoreObserver() = default;

	virtual void Notify(Shining::GameObject* const pSubject, const int eventID, void* pData) noexcept override;
private:
	int m_Score;
	int m_GemPickupStreak;
	const int m_GemPickupStreakMax;
};

