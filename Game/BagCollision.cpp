#include "BagCollision.h"
#include "Enums.h"
#include "BagFallingState.h"
#include "BagIdleState.h"
#include "ShiningEnginePCH.h"

BagCollision::BagCollision(Shining::HealthComponent* const pPlayerHealth)
	:CollisionBehavior()
	, m_pPlayerHealth{pPlayerHealth}
{
}

void BagCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	Shining::StateComponent* const pBagState{ pOwnerObject->GetComponent<Shining::StateComponent>() };
	switch (collidedTag)
	{
		case int(CollisionTags::player) :
			if (pBagState->IsCurrentState<BagFallingState>())
			{
				m_pPlayerHealth->GetHit(1); //attempt to deal 1 damage to player
			}
			break;
		case int(CollisionTags::wall) :
			ResolveWorldCollision(pOwnerObject);
			break;
		default:
			break;
	}
}

void BagCollision::ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept
{
	Shining::StateComponent* const pState{ pOwnerObject->GetComponent<Shining::StateComponent>() };
	if (pState->IsCurrentState<BagFallingState>()) //make sure bag is currently falling
	{
		//bag has hit floor	
		Shining::AudioPlayer::GetInstance().StopAllEffects(); //stop the falling sound
		//break bag, spawn gold
		pOwnerObject->SetActive(false);
		Shining::SpawnComponent* const pGoldSpawn{ pOwnerObject->GetComponent<Shining::SpawnComponent>() };
		const glm::vec2& ownerPos{ pOwnerObject->GetPosition() };
		pGoldSpawn->SpawnObject(ownerPos.x, ownerPos.y);
	}
	else
	{
		//bag is in idle state and is colliding with world, stop it from falling
		static_cast<BagIdleState*>(pState->GetCurrentState())->DenyFall();
		
	}
}