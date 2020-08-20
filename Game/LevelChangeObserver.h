#pragma once
#include "Observer.h"
#include <vector>


class LevelChangeObserver final : public Shining::Observer
{
public:
	explicit LevelChangeObserver();
	virtual ~LevelChangeObserver() = default;
	void AddGemGoal(const unsigned int nrGemsToAdvance) noexcept;
	void AddEnemyKillsGoal(const unsigned int nrKillsToAdvance) noexcept;

	virtual void Notify(Shining::GameObject* const pSubject, const int eventID, void* pData) noexcept override;
private:
	std::vector<unsigned int> m_GemGoals;
	std::vector<unsigned int> m_EnemyKillGoals;
	unsigned int m_GoalIdx;
	unsigned int m_NrGemsPickedUp;
	unsigned int m_NrEnemiesKilled;

};

