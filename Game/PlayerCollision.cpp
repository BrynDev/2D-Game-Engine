#include "PlayerCollision.h"
#include "Enums.h"

void PlayerCollision::ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::gem):
		{
			pObject->NotifyObservers(int(ObservedEvents::gemPickup));
			break;
		}
		default:
		{
			break;
		}
		
	}
}