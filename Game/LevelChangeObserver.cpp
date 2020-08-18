#include "LevelChangeObserver.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

LevelChangeObserver::LevelChangeObserver()
	:Observer()
	, m_NrRequiredGems{0}
	, m_NrRequiredKills{0}
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

	if (m_NrGemsPickedUp >= m_NrRequiredGems || m_NrEnemiesKilled >= m_NrRequiredKills)
	{
		//change scene
		m_NrGemsPickedUp = 0;
		m_NrEnemiesKilled = 0;
		Shining::SceneManager::GetInstance().AdvanceScene();
	}
}

void LevelChangeObserver::SetRequiredGems(const unsigned int nrGems) noexcept
{
	m_NrRequiredGems = nrGems;
}
void LevelChangeObserver::SetRequiredKills(const unsigned int nrEnemies) noexcept
{
	m_NrRequiredKills = nrEnemies;
}