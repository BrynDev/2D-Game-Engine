#include "PlayerCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void PlayerCollision::ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::gem):
			pObject->NotifyObservers(int(ObservedEvents::gemPickup));
			break;	
		case int(CollisionTags::goldBag):
			pObject->GetComponent<Shining::PhysicsComponent>()->BlockMovement();
			break;
		case int(CollisionTags::wall):
			pObject->GetComponent<Shining::PhysicsComponent>()->BlockMovement();
			break;
		default:
			break;		
	}
}