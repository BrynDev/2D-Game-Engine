#include "PlayerCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void PlayerCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::enemy) :
			pOwnerObject->GetComponent<Shining::HealthComponent>()->GetHit(1);
			break;
		case int(CollisionTags::gem):
			pOwnerObject->NotifyObservers(int(ObservedEvents::gemPickup));
			break;	
		case int(CollisionTags::gold):
			pOwnerObject->NotifyObservers(int(ObservedEvents::goldPickup));
			break;
		case int(CollisionTags::goldBag):
			pOwnerObject->GetComponent<Shining::PhysicsComponent>()->BlockMovement();
			break;
		case int(CollisionTags::wall):
			pOwnerObject->GetComponent<Shining::PhysicsComponent>()->BlockMovement();
			break;
		default:
			break;		
	}
}

void PlayerCollision::ResolveWorldCollision(Shining::GameObject* const /*pOwnerObject*/) const noexcept
{
	//don't affect the player, tile breaking is handled in the collision manager
}