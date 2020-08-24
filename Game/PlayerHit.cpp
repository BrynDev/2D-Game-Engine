#include "PlayerHit.h"
#include "Enums.h"
#include "DyingState.h"
#include "ShiningEnginePCH.h"

void PlayerHit::OnHit(Shining::GameObject* const pHitObject, const int damageTaken) const noexcept
{
	if (damageTaken > 0) //player took damage
	{
		
		//set player state to dying, reset current stage
		Shining::StateComponent* const pPlayerState{ pHitObject->GetComponent<Shining::StateComponent>() };
		if (pPlayerState->IsCurrentState<DyingState>())
		{
			//player is in dying animation, don't take another hit
			return;
		}
		Shining::HealthComponent* const pPlayerHealth{ pHitObject->GetComponent<Shining::HealthComponent>() };
		pPlayerHealth->TakeDamage(damageTaken);
		pHitObject->NotifyObservers(int(ObservedEvents::playerHit)); //decrease life counter
		pPlayerState->ChangeState<DyingState>();
	}

	//if damageTaken is smaller than 0, the player just got an extra life and nothing should happen on hit
	
}

void PlayerHit::OnDeath(Shining::GameObject* const /*pDeadObject*/) const noexcept
{
	//game over
	Shining::AudioPlayer::GetInstance().StopAllEffects();
	Shining::SceneManager::GetInstance().GoToFinalScene();
}