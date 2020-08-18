#pragma once
#include "Observer.h"


class LevelChangeObserver final : public Shining::Observer
{
public:
	LevelChangeObserver();
	virtual ~LevelChangeObserver() = default;
	void SetRequiredGems(const unsigned int nrGems) noexcept;
	void SetRequiredKills(const unsigned int nrEnemies) noexcept;

	virtual void Notify(Shining::GameObject* const pSubject, const int eventID, void* pData) noexcept override;
private:
	unsigned int m_NrRequiredGems;
	unsigned int m_NrRequiredKills;
	unsigned int m_NrGemsPickedUp;
	unsigned int m_NrEnemiesKilled;

};

