#include "BagCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"
#include "BagFallingState.h"

void BagCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	Shining::StateComponent* pState{ nullptr };

	switch (collidedTag)
	{
		case int(CollisionTags::player) :
			//kill
			break;
		case int(CollisionTags::enemy):
			//kill
			break;
		case int(CollisionTags::wall):
			pOwnerObject->GetComponent<Shining::PhysicsComponent>()->BlockMovement();
			//if falling onto the bottom wall, break the bag
			pState = pOwnerObject->GetComponent<Shining::StateComponent>();
			if (pState->IsCurrentState<BagFallingState>())
			{
				static_cast<BagFallingState*>(pState->GetCurrentState())->HitBottomWall();
			}
			break;
		default:
			break;
	}
}