#include "LifeObserver.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

LifeObserver::LifeObserver(Shining::TextComponent* const pLivesText, const int lives)
	:Observer()
	, m_pLivesText{pLivesText}
	, m_NrLives{lives}
{
}

void LifeObserver::Notify(Shining::GameObject* const /*pSubject*/, const int eventID, void* pData) noexcept
{
	bool wasNrLivesChanged{ false };
	switch (eventID)
	{
		case int(ObservedEvents::playerHit) :
			wasNrLivesChanged = true;
			/*--m_NrLives;
			static_cast<int*>(pData);
			//m_pLivesText->SetText("x " + m_NrLives);
			
			static_cast<int*>(pData);*/
			break;
		case int(ObservedEvents::extraLifeEarned) :
			wasNrLivesChanged = true;
			/*++m_NrLives;
			m_pLivesText->SetText("x " + m_NrLives);*/
			break;
		default:
			break;
	}

	if (wasNrLivesChanged)
	{
		int* pNrLives{ static_cast<int*>(pData) };
		std::string newText{ "x " + std::to_string(*pNrLives) };
		m_pLivesText->SetText(newText);
	}

	/*if (m_NrLives < 0)
	{
		pSubject->NotifyObservers(int(ObservedEvents::outOfLives));
	}*/
}