#include "LifeObserver.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

LifeObserver::LifeObserver(Shining::TextComponent* const pLivesText)
	:Observer()
	, m_pLivesText{pLivesText}
{
}

void LifeObserver::Notify(Shining::GameObject* const pSubject, const int eventID, void* /*pData*/) noexcept
{
	//bool wasNrLivesChanged{ false };
	//bool shouldIncreaseCount{ false };
	bool shouldIncrease{ false };
	bool shouldDecrease{ false };
	switch (eventID)
	{
		case int(ObservedEvents::playerHit) :
			//wasNrLivesChanged = true;
			shouldDecrease = true;
			break;
		case int(ObservedEvents::extraLifeEarned) :
			pSubject->GetComponent<Shining::HealthComponent>()->TakeDamage(-1); //deal -1 damage to actually give the player an extra life
			//wasNrLivesChanged = true;
			//shouldIncreaseCount = true;
			shouldIncrease = true;
			break;
		default:
			break;
	}

	/*if (wasNrLivesChanged)
	{
		Shining::HealthComponent* const pHealth{ pSubject->GetComponent<Shining::HealthComponent>() };
		int currentHealth{ pHealth->GetCurrentHealth() };
		if (shouldIncreaseCount)
		{
			++currentHealth; //there is no SwapBuffer() call between increasing health and updating the text, so increment it once to make the text correct
		}

		std::string newText{ "x " + std::to_string(currentHealth) };
		m_pLivesText->SetText(newText);
	}*/

	if (shouldIncrease)
	{
		Shining::HealthComponent* const pHealth{ pSubject->GetComponent<Shining::HealthComponent>() };
		int currentHealth{ pHealth->GetCurrentHealth() };
		int newHealth{ currentHealth + 1 };

		std::string newText{ "x " + std::to_string(newHealth) };
		m_pLivesText->SetText(newText);
	}
	if (shouldDecrease)
	{
		Shining::HealthComponent* const pHealth{ pSubject->GetComponent<Shining::HealthComponent>() };
		int currentHealth{ pHealth->GetCurrentHealth() };
		int newHealth{ currentHealth - 1 };

		std::string newText{ "x " + std::to_string(newHealth) };
		m_pLivesText->SetText(newText);
	}
}