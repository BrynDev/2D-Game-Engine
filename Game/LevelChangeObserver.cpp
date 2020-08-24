#include "LevelChangeObserver.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

LevelChangeObserver::LevelChangeObserver()
	:Observer()
	, m_GoalIdx{0}
	, m_NrGemsPickedUp{0}
	, m_NrEnemiesKilled{0}
{

}

void LevelChangeObserver::Notify(Shining::GameObject* const /*pSubject*/, const int eventID, void* /*pData*/) noexcept
{
	switch (eventID)
	{
		case int(ObservedEvents::gemPickup):
			++m_NrGemsPickedUp;
		break;
		case int(ObservedEvents::enemyKill):
			++m_NrEnemiesKilled;
			break;
	default:
		break;
	}

	if (m_NrGemsPickedUp >= m_GemGoals[m_GoalIdx] || m_NrEnemiesKilled >= m_EnemyKillGoals[m_GoalIdx])
	{
		//change scene
		m_NrGemsPickedUp = 0;
		m_NrEnemiesKilled = 0;
		++m_GoalIdx;
		Shining::SceneManager::GetInstance().AdvanceScene();
	}
}

void LevelChangeObserver::AddGemGoal(const unsigned int nrGemsToAdvance) noexcept
{
	m_GemGoals.push_back(nrGemsToAdvance);
}

void LevelChangeObserver::AddEnemyKillsGoal(const unsigned int nrKillsToAdvance) noexcept
{
	m_EnemyKillGoals.push_back(nrKillsToAdvance);
}