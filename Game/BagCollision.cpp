#include "BagCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"
#include "BagFallingState.h"
#include "BagIdleState.h"

void BagCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::player) :
			//kill
			break;
		case int(CollisionTags::enemy):
			//kill
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