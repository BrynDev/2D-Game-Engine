#include "PlayerCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void PlayerCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
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