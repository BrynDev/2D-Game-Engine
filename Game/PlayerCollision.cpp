#include "PlayerCollision.h"
#include "Enums.h"
#include "PhysicsComponent.h"

void PlayerCollision::ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::gem):
		{
			pObject->NotifyObservers(int(ObservedEvents::gemPickup));
			//pObject->GetComponent<Shining::PhysicsComponent>()->
			break;
		}
		default:
		{
			break;
		}
		
	}
}