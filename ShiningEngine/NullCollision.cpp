#include "ShiningEnginePCH.h"
#include "NullCollision.h"

Shining::NullCollision::NullCollision()
	:CollisionBehavior()
{
}

void Shining::NullCollision::ResolveCollision(Shining::GameObject* const /*pObject*/, const int /*collidedTag*/) const noexcept
{
	//empty function
}

void Shining::NullCollision::ResolveWorldCollision(Shining::GameObject* const /*pOwnerObject*/) const noexcept
{
	//empty
}