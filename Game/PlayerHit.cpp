#include "PlayerHit.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void PlayerHit::OnHit(Shining::GameObject* const pHitObject, const int damageTaken) const noexcept
{

	Shining::HealthComponent* const pPlayerHealth{ pHitObject->GetComponent<Shining::HealthComponent>() };
	const int currentHealth{ pPlayerHealth->GetCurrentHealth() };

	int eventIDToSend{};
	if (damageTaken > 0)
	{
		eventIDToSend = int(ObservedEvents::playerHit);
	}
	/*else
	{
		eventIDToSend = int(ObservedEvents::extraLifeEarned);
	}*/
	
	pHitObject->NotifyObservers(eventIDToSend, (void*)(&currentHealth));
	//set player to dying state
}

void PlayerHit::OnDeath(Shining::GameObject* const pDeadObject) const noexcept
{
	pDeadObject->NotifyObservers(int(ObservedEvents::outOfLives));
	//game over
}