#include "PickupCollision.h"
#include "Enums.h"

void PickupCollision::ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::player):
			pObject->SetActive(true);
			//pObject->SetActive(false);
		break;
	default:
		break;
	}
}