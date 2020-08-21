#include "FireballCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void FireballCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	bool hasHit{ false };
	switch (collidedTag)
	{
		case int(CollisionTags::enemy) :
			//kill enemy
			hasHit = true;
			break;
		case int(CollisionTags::goldBag) :
			hasHit = true;
			break;
		case int(CollisionTags::wall) :
			hasHit = true;
			break;
		default:
			break;
	}

	//Shining::CollisionComponent* pCollision{ pOwnerObject->GetComponent<Shining::CollisionComponent>() };
	if (hasHit /*|| pCollision->HasHitWorld()*/)
	{
		pOwnerObject->SetActive(false);
	}
}
