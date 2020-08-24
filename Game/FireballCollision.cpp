#include "FireballCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void FireballCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	bool hasHit{ false };
	switch (collidedTag)
	{
		case int(CollisionTags::enemy) :
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

	if (hasHit)
	{
		pOwnerObject->SetActive(false);
	}
}

void FireballCollision::ResolveWorldCollision(Shining::GameObject* const pOwnerObject) const noexcept
{
	pOwnerObject->SetActive(false);
	Shining::PhysicsComponent* const pPhysics{ pOwnerObject->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false);
}
