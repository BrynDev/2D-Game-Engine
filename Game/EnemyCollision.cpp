#include "EnemyCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void EnemyCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
		case int(CollisionTags::goldBag) :
			pOwnerObject->SetActive(false);
			pOwnerObject->NotifyObservers(int(ObservedEvents::enemyKill));
			break;
		case int(CollisionTags::fireBall) :
			pOwnerObject->SetActive(false);
			pOwnerObject->NotifyObservers(int(ObservedEvents::enemyKill));
			break;
		case int(CollisionTags::wall) :
			ResolveWorldCollision(pOwnerObject);
			break;
		default:
			break;
	}
}

void EnemyCollision::ResolveWorldCollision(Shining::GameObject* const /*pOwnerObject*/) const noexcept
{
}