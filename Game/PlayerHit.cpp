#include "PlayerHit.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void PlayerHit::OnHit(Shining::GameObject* const pHitObject, const int damageTaken) const noexcept
{
	if (damageTaken > 0) //player took damage
	{
		/*Shining::HealthComponent* const pPlayerHealth{ pHitObject->GetComponent<Shining::HealthComponent>() };
		const int currentHealth{ pPlayerHealth->GetCurrentHealth() };
		const int eventIDToSend{ int(ObservedEvents::playerHit) };*/
		pHitObject->NotifyObservers(int(ObservedEvents::playerHit)); //decrease life counter
		//set player state to dying, reset current stage
	}

	//if damageTaken is smaller than 0, the player got an extra life and nothing should happen on hit
	
}

void PlayerHit::OnDeath(Shining::GameObject* const pDeadObject) const noexcept
{
	pDeadObject->NotifyObservers(int(ObservedEvents::outOfLives));
	//game over
}